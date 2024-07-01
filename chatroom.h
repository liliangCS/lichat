#ifndef CHATROOM_H
#define CHATROOM_H

#include <QString>
#include <QWebSocket>

//消息类型
enum MessageType {
    ENTER_ROOM_SUCCESS,
    ENTER_ROOM_FAILED,
    SOMEONE_ENTER_ROOM,
    SOMEONE_LEAVE_ROOM,
    SEND_TEXT,
    SEND_RICH_TEXT
};

class ChatRoom
{
public:
    ChatRoom(const ChatRoom &) = delete;
    ChatRoom& operator = (const ChatRoom &) = delete;

    void enterRoom(QString &username);
    void leaveRoom(QString &username);

    void updateMemberCount(int count);
    void updateUsername(QString &username);

    static ChatRoom* getInstance();
private:
    static ChatRoom *instance;
    QWebSocket *ws;
    int m_memberCount;
    QString m_username;

    ChatRoom(QWebSocket *ws);
};

#endif // CHATROOM_H
