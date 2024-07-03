#ifndef CHATROOM_H
#define CHATROOM_H

#include <QObject>
#include <QString>
#include <QWebSocket>

//消息类型
enum MessageType {
    ENTER_ROOM_SUCCESS,
    ENTER_ROOM_FAILED,
    SOMEONE_ENTER_ROOM,
    SOMEONE_LEAVE_ROOM,
    SEND_PLAIN_TEXT,
    SEND_RICH_TEXT
};

class ChatRoom : public QObject
{
    Q_OBJECT
public:
    ChatRoom(const ChatRoom &) = delete;
    ChatRoom& operator = (const ChatRoom &) = delete;

    static ChatRoom* getInstance();

    void enterRoom(QString &username);
    void leaveRoom();

    int getUserCount();
    void setUserCount(int count);

    QString& getUsername();
    void setUsername(QString &username);

    void sendPlainTextMsg(QString &contentStr);


private:
    static ChatRoom *instance;
    QWebSocket *ws;
    int m_userCount;
    QString m_username;

    explicit ChatRoom(QWebSocket *ws, QObject *parent = nullptr);

public slots:
    void onEnterRoomSuccess(QString &username);
    void onEnterRoomFailed();
    void onSomeoneEnterRoom(QString &username, int userCount);
    void onSomeoneLeaveRoom(QString &username, int userCount);
    void onSendPlainText(QString &sender, QString &contentStr, QString &timeStr);
    void onSendRichText();
};

#endif // CHATROOM_H
