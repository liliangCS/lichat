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
    //初始化ChatRoom单例
    ChatRoom *cr = ChatRoom::getInstance();

    //进入聊天室成功
    QObject::connect(wsc, &WebSocketClient::enterRoomSuccess, [&](QString &username){
        ld.close();
        hw.show();
        cr->onEnterRoomSuccess(username);
        hw.updateUIUsername(username);
    });
    //进入聊天室失败
    QObject::connect(wsc, &WebSocketClient::enterRoomFailed, [&](){
        cr->onEnterRoomFailed();
    });
    //某人进入聊天室
    QObject::connect(wsc, &WebSocketClient::someoneEnterRoom, [&](QString &username, int userCount){
        cr->onSomeoneEnterRoom(username, userCount);
        hw.updateUIUserCount(userCount);
    });
    //某人离开聊天室
    QObject::connect(wsc, &WebSocketClient::someoneLeaveRoom, [&](QString &username, int userCount){
        if (username == cr->getUsername()) {
            hw.close();
            ld.show();
        }
        cr->onSomeoneLeaveRoom(username, userCount);
        hw.updateUIUserCount(userCount);
    });
    //与服务器连接状态改变
    QObject::connect(wsc, &WebSocketClient::connStateChange, [&](ConnState &state){
        hw.updateUIConnState(state);
    });

    QObject::connect(wsc, &WebSocketClient::sendText, [&](){
        cr->onSendText();
    });

    QObject::connect(wsc, &WebSocketClient::sendRichText, [&](){
        cr->onSendRichText();
    });



    return a.exec();
}
