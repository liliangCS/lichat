#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QTimer>
#include <QWebSocket>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    WebSocketClient(const WebSocketClient&) = delete;
    WebSocketClient& operator = (const WebSocketClient&) = delete;

    static WebSocketClient* getInstance();

private:
    static WebSocketClient *instance;

    QWebSocket *m_webSocket;
    QUrl m_url;
    bool m_connState;
    QTimer *m_reconnTimer;

    explicit WebSocketClient(const QUrl &url, QObject *parent = nullptr);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onDisconnected();
    void onTimeoutReconnect();
};

#endif // WEBSOCKETCLIENT_H
