#include "logindialog.h"
#include <QApplication>
#include "websocketclient.h"
#include "chatroom.h"
#include "homewidget.h"
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HomeWidget hw;
    LoginDialog ld;
    ld.show();
    //初始化WebSocketClient单例
    WebSocketClient *wsc = WebSocketClient::getInstance();
    //进入房间信号处理
    QObject::connect(wsc, &WebSocketClient::enterRoom, [&ld, &hw](){
        ld.close();
        qDebug() << "enter room success";
        hw.show();
    });

    //初始化ChatRoom单例
    ChatRoom::getInstance();
    return a.exec();
}
