#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QTimer>
#include <QWebSocket>
#include "chatroom.h"

enum ConnState {
    CONNECTED,
    DISCONNECTED
};

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    WebSocketClient(const WebSocketClient&) = delete;
    WebSocketClient& operator = (const WebSocketClient&) = delete;

    static WebSocketClient* getInstance();
    //获取与服务器的连接状态
    ConnState getConnState();

    //获取websocket连接
    QWebSocket* getWebSocket();

    //获取服务端url地址
    QUrl& getUrl();

    //关闭websocket连接
    void closeConn();
private:
    static WebSocketClient *instance;

    QWebSocket *m_webSocket;
    QUrl m_url;
    ConnState m_connState;
    QTimer *m_reconnTimer;

    explicit WebSocketClient(const QUrl &url, QObject *parent = nullptr);

signals:
    void enterRoomSuccess(QString &username);
    void enterRoomFailed();
    void someoneEnterRoom(QString &username, int userCount, QString &timeStr);
    void someoneLeaveRoom(QString &username, int userCount, QString &timeStr);
    void sendText();
    void sendRichText();
    void connStateChange(ConnState &state);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onDisconnected();
    void onTimeoutReconnect();
};

#endif // WEBSOCKETCLIENT_H
