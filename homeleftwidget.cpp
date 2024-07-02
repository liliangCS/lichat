#include "homeleftwidget.h"
#include "ui_homeleftwidget.h"
#include "helper.h"
#include "chatroom.h"

HomeLeftWidget::HomeLeftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeLeftWidget)
{
    ui->setupUi(this);
    Helper::loadStyleSheet(this, ":/qss/homeLeftWidget.qss");

    //leaveBtn
    connect(ui->leaveBtn, &QPushButton::clicked, [](){
        ChatRoom::getInstance()->leaveRoom();
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
