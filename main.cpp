#include "logindialog.h"
#include <QApplication>
#include "websocketclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog w;
    w.show();
    //初始化WebSocketClient单例
    WebSocketClient::getInstance();
    return a.exec();
}
