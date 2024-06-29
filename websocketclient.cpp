#include "websocketclient.h"

WebSocketClient::WebSocketClient(const QUrl &url, QObject *parent) : QObject(parent), m_url(url)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    m_webSocket.open(url);
}

void WebSocketClient::onConnected()
{
    qDebug() << "WebSocket connected";
}

void WebSocketClient::onTextMessageReceived(QString message)
{

}

void WebSocketClient::onDisconnected()
{
    qDebug() << "WebSocket disConnected";
}
