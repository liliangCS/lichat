#include "websocketclient.h"

WebSocketClient* WebSocketClient::instance = nullptr;

WebSocketClient* WebSocketClient::getInstance()
{
    if (instance == nullptr) {
        instance = new WebSocketClient(QUrl("ws://127.0.0.1:8115"));
    }
    return instance;
}

WebSocketClient::WebSocketClient(const QUrl &url, QObject *parent) : QObject(parent), m_webSocket(new QWebSocket()), m_url(url), m_connState(false), m_reconnTimer(new QTimer(this))
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
    m_connState = true;
    m_reconnTimer->stop();
}

void WebSocketClient::onTextMessageReceived(QString message)
{
    qDebug() << message;
}

void WebSocketClient::onDisconnected()
{
    qDebug() << "WebSocket disconnected";
    m_connState = false;
    m_reconnTimer->start(5000);
}

void WebSocketClient::onTimeoutReconnect()
{
    if (!m_connState)
    {
        qDebug() << "try to reconnect...";
        m_webSocket->abort();
        m_webSocket->open(m_url);
    }
}

