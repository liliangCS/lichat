#include "logindialog.h"
#include <QApplication>
#include "websocketclient.h"
#include "chatroom.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog w;
    w.show();
    //初始化WebSocketClient单例
    WebSocketClient::getInstance();
    //初始化ChatRoom单例
    ChatRoom::getInstance();
    return a.exec();
}
