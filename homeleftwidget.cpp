#include "homeleftwidget.h"
#include "ui_homeleftwidget.h"
#include "helper.h"
#include "chatroom.h"
#include <QDebug>

HomeLeftWidget::HomeLeftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeLeftWidget), m_roomIOMessageList(new QStringList())
{
    ui->setupUi(this);
    Helper::loadStyleSheet(this, ":/qss/homeLeftWidget.qss");

    //leaveBtn
    connect(ui->leaveBtn, &QPushButton::clicked, [](){
        ChatRoom::getInstance()->leaveRoom();
    });

    connect(this, &HomeLeftWidget::newRoomIOMessage, [&](QString &msg){
        qDebug() << msg;
        updateUIRoomIOMsg(msg);
    });
}

HomeLeftWidget::~HomeLeftWidget()
{
    delete ui;
}

void HomeLeftWidget::updateUIUsername(QString &username)
{
    ui->nameLabel->setText(username);
}

void HomeLeftWidget::updateUIUserCount(int userCount)
{
    ui->onlineCountLabel->setText(QString::number(userCount));
}

void HomeLeftWidget::updateUIConnState(ConnState &state)
{
    if (state == ConnState::CONNECTED) {
        ui->connStateLabel->setText("连接正常");
    }
    else
    {
        ui->connStateLabel->setText("连接断开，重连中...");
    }
}

void HomeLeftWidget::updateUIRoomIOMsg(QString &msg)
{
    ui->roomIOMsgTextEdit->append(msg);
}

void HomeLeftWidget::addRoomIOMessage(QString &msg)
{
    m_roomIOMessageList->append(msg);
    emit newRoomIOMessage(msg);
}

void HomeLeftWidget::clearRoomIOMessageList()
{
    m_roomIOMessageList->clear();
    ui->roomIOMsgTextEdit->clear();
}

QStringList *HomeLeftWidget::getRoomIOMessageList()
{
    return m_roomIOMessageList;
}
