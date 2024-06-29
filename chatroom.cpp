#include "chatroom.h"

ChatRoom* ChatRoom::instance = nullptr;


void ChatRoom::send(MessageType msgType)
{

}

void ChatRoom::send(MessageType msgType, QString &msg)
{

}

void ChatRoom::send(MessageType msgType, QString &msg, QString &emojiStr)
{

}

ChatRoom *ChatRoom::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ChatRoom();
    }
    return instance;
}

ChatRoom::ChatRoom()
{

}
