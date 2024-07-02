#include "websocketclient.h"
#include <QJsonDocument>
#include <QJsonObject>

WebSocketClient* WebSocketClient::instance = nullptr;

WebSocketClient* WebSocketClient::getInstance()
{
    if (instance == nullptr) {
        instance = new WebSocketClient(QUrl("ws://127.0.0.1:8115"));
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

        emit someoneEnterRoom(username, userCount);
    }

    else if (msgType == MessageType::SOMEONE_LEAVE_ROOM)
    {
        QString username = msgObj["username"].toString();
        int userCount = msgObj["userCount"].toInt();

        emit someoneLeaveRoom(username, userCount);
    }

    else if (msgType == MessageType::SEND_TEXT)
    {
        qDebug() << msgObj;
    }

    else if (msgType == MessageType::SEND_RICH_TEXT)
    {
        qDebug() << msgObj;
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

