#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(const QUrl &url, QObject *parent = nullptr);

private:
    QWebSocket m_webSocket;
    QUrl m_url;

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onDisconnected();
};

#endif // WEBSOCKETCLIENT_H
