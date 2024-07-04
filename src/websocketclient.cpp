#include <QJsonDocument>
#include <QJsonObject>
#include "include/websocketclient.h"
#include "include/helper.h"

WebSocketClient* WebSocketClient::instance = nullptr;

WebSocketClient* WebSocketClient::getInstance()
{
    if (instance == nullptr) {
        IniConfig config = Helper::loadIniConfig();
        QString url = QString("ws://%1:%2").arg(config.server_ip).arg(config.server_port);
        qDebug() << url;
        instance = new WebSocketClient(QUrl(url));
    }
    return instance;
}

ConnState WebSocketClient::getConnState()
{
    return m_connState;
}

QWebSocket *WebSocketClient::getWebSocket()
{
    return m_webSocket;
}

QUrl &WebSocketClient::getUrl()
{
    return m_url;
}

void WebSocketClient::closeConn()
{
    m_webSocket->close();
}

WebSocketClient::WebSocketClient(const QUrl &url, QObject *parent) : QObject(parent), m_webSocket(new QWebSocket()), m_url(url), m_connState(ConnState::DISCONNECTED), m_reconnTimer(new QTimer(this))
{
    connect(m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    connect(m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(m_reconnTimer, &QTimer::timeout, this, &WebSocketClient::onTimeoutReconnect);

    m_webSocket->open(url);
}

void WebSocketClient::onConnected()
{
    qDebug() << "WebSocket connected";
    m_connState = ConnState::CONNECTED;
    emit connStateChange(m_connState);
    m_reconnTimer->stop();
}

void WebSocketClient::onTextMessageReceived(QString message)
{
    QJsonDocument msgDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject msgObj = msgDoc.object();

    MessageType msgType = static_cast<MessageType>(msgObj["type"].toInt());

    if (msgType == MessageType::ENTER_ROOM_SUCCESS)
    {
        QString username = msgObj["username"].toString();

        emit enterRoomSuccess(username);
    }

    else if (msgType == MessageType::ENTER_ROOM_FAILED)
    {
        emit enterRoomFailed();
    }

    else if (msgType == MessageType::SOMEONE_ENTER_ROOM)
    {
        QString username = msgObj["username"].toString();
        int userCount = msgObj["userCount"].toInt();
        QString timeStr = msgObj["timeStr"].toString();

        emit someoneEnterRoom(username, userCount, timeStr);
    }

    else if (msgType == MessageType::SOMEONE_LEAVE_ROOM)
    {
        QString username = msgObj["username"].toString();
        int userCount = msgObj["userCount"].toInt();
        QString timeStr = msgObj["timeStr"].toString();

        emit someoneLeaveRoom(username, userCount, timeStr);
    }

    else if (msgType == MessageType::SEND_PLAIN_TEXT)
    {
        QString sender = msgObj["sender"].toString();
        QString contentStr = msgObj["contentStr"].toString();
        QString timeStr = msgObj["timeStr"].toString();

        emit sendPlainText(sender, contentStr, timeStr);
    }

    else if (msgType == MessageType::SEND_RICH_TEXT)
    {
        QString sender = msgObj["sender"].toString();
        QString contentStr = msgObj["contentStr"].toString();
        QString emojiStr = msgObj["emojiStr"].toString();
        QString timeStr = msgObj["timeStr"].toString();

        emit sendRichText(sender, contentStr, emojiStr, timeStr);
    }
}

void WebSocketClient::onDisconnected()
{
    qDebug() << "WebSocket disconnected";
    m_connState = ConnState::DISCONNECTED;
    emit connStateChange(m_connState);
    m_reconnTimer->start(5000);
}

void WebSocketClient::onTimeoutReconnect()
{
    if (m_connState == ConnState::DISCONNECTED)
    {
        qDebug() << "try to reconnect...";
        m_webSocket->abort();
        m_webSocket->open(m_url);
    }
}

