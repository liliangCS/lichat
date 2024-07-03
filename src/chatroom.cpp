#include <QJsonObject>
#include <QJsonDocument>
#include <functional>
#include <QMessageBox>
#include "include/chatroom.h"
#include "include/websocketclient.h"

ChatRoom* ChatRoom::instance = nullptr;


void ChatRoom::enterRoom(QString &username)
{
    QJsonObject messageObj;
    messageObj["type"] = MessageType::SOMEONE_ENTER_ROOM;
    messageObj["sender"] = username;
    QJsonDocument messageDoc(messageObj);
    QString messageStr = messageDoc.toJson(QJsonDocument::Compact);
    ws->sendTextMessage(messageStr);
}

void ChatRoom::leaveRoom()
{
    QJsonObject messageObj;
    messageObj["type"] = MessageType::SOMEONE_LEAVE_ROOM;
    messageObj["sender"] = m_username;
    QJsonDocument messageDoc(messageObj);
    QString messageStr = messageDoc.toJson(QJsonDocument::Compact);
    ws->sendTextMessage(messageStr);
}

int ChatRoom::getUserCount()
{
    return m_userCount;
}

void ChatRoom::setUserCount(int count)
{
    m_userCount = count;
}

void ChatRoom::setUsername(QString &username)
{
    m_username = username;
}

void ChatRoom::sendPlainTextMsg(QString &contentStr)
{
    QJsonObject messageObj;
    messageObj["type"] = MessageType::SEND_PLAIN_TEXT;
    messageObj["sender"] = m_username;
    messageObj["contentStr"] = contentStr;
    QJsonDocument messageDoc(messageObj);
    QString messageStr = messageDoc.toJson(QJsonDocument::Compact);
    ws->sendTextMessage(messageStr);
}

QString& ChatRoom::getUsername()
{
    return m_username;
}

ChatRoom *ChatRoom::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ChatRoom(WebSocketClient::getInstance()->getWebSocket());
    }
    return instance;
}

ChatRoom::ChatRoom(QWebSocket *ws, QObject *parent): QObject(parent),  ws(ws), m_userCount(0)
{
}

void ChatRoom::onEnterRoomSuccess(QString &username)
{
    qDebug() << "enter room success";
    setUsername(username);
}

void ChatRoom::onEnterRoomFailed()
{
    qDebug() << "enter room failed";
    QMessageBox::information(nullptr, "提示", "聊天室内存在同名用户，进入聊天室失败");
}

void ChatRoom::onSomeoneEnterRoom(QString &username, int userCount)
{
    setUserCount(userCount);
    qDebug() << username << " enter room; " << "room user count is " << userCount;
}

void ChatRoom::onSomeoneLeaveRoom(QString &username, int userCount)
{
    setUserCount(userCount);
    qDebug() << username << " leave room; " << "room user count is " << userCount;
}

void ChatRoom::onSendPlainText(QString &sender, QString &contentStr, QString &timeStr)
{
    qDebug() << "timeStr: " << timeStr;
    qDebug() << "sender: " << sender;
    qDebug() << "contentStr: " << contentStr;
}

void ChatRoom::onSendRichText()
{
    qDebug() << "send rich text";
}