#ifndef CHATROOM_H
#define CHATROOM_H

#include <QString>
#include <QWebSocket>

//消息类型
enum MessageType {
    ENTER_ROOM_MSG,
    ENTER_ROOM_MSG_FAILED,
    LEAVE_ROOM_MSG,
    PLAIN_TEXT_MSG,
    RICH_TEXT_MSG
};

class ChatRoom
{
public:
    ChatRoom(const ChatRoom &) = delete;
    ChatRoom& operator = (const ChatRoom &) = delete;

    void enterRoom(QString &username);
    void leaveRoom(QString &username);

    void updateMemberCount(int count);

    static ChatRoom* getInstance();
private:
    static ChatRoom *instance;
    QWebSocket *ws;
    int m_memberCount;

    ChatRoom(QWebSocket *ws);
};

#endif // CHATROOM_H
