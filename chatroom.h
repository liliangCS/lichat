#ifndef CHATROOM_H
#define CHATROOM_H

#include <QString>


//消息类型
enum MessageType {
    ENTER_ROOM_MSG,
    LEAVE_ROOM_MSG,
    PLAIN_TEXT_MSG,
    RICH_TEXT_MSG
};

class ChatRoom
{
public:
    ChatRoom(const ChatRoom &) = delete;
    ChatRoom& operator = (const ChatRoom &) = delete;

    //发送聊天室消息
    void send(MessageType msgType);
    void send(MessageType msgType, QString &msg);
    void send(MessageType msgType, QString &msg, QString& emojiStr);

    static ChatRoom* getInstance();
private:
    static ChatRoom *instance;
    ChatRoom();
};

#endif // CHATROOM_H
