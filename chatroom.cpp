#include "chatroom.h"
#include "websocketclient.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <functional>

ChatRoom* ChatRoom::instance = nullptr;


void ChatRoom::enterRoom(QString &username)
{
    QJsonObject messageObj;
    messageObj["type"] = MessageType::ENTER_ROOM_MSG;
    messageObj["sender"] = username;
    QJsonDocument messageDoc(messageObj);
    QString messageStr = messageDoc.toJson(QJsonDocument::Compact);
    ws->sendTextMessage(messageStr);
}

void ChatRoom::leaveRoom(QString &username)
{
    QJsonObject messageObj;
    messageObj["type"] = MessageType::LEAVE_ROOM_MSG;
    messageObj["sender"] = username;
    QJsonDocument messageDoc(messageObj);
    QString messageStr = messageDoc.toJson(QJsonDocument::Compact);
    ws->sendTextMessage(messageStr);
}

void ChatRoom::updateMemberCount(int count)
{
    m_memberCount = count;
}

ChatRoom *ChatRoom::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ChatRoom(WebSocketClient::getInstance()->getWebSocket());
    }
    return instance;
}

ChatRoom::ChatRoom(QWebSocket *ws): ws(ws), m_memberCount(0)
{
}
