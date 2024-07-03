#include "ui_homewidget.h"
#include <QDesktopWidget>
#include <QIcon>
#include <QMouseEvent>
#include "include/helper.h"
#include "include/chatroom.h"
#include "include/homewidget.h"

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWidget)
{
    ui->setupUi(this);
    Helper::loadStyleSheet(this, ":/qss/homeWidget.qss");
    setWindowTitle("世界之窗聊天室");
    setWindowIcon(QIcon(":/images/logo.ico"));
    setMinimumSize(600, 400);
    ui->leftWidget->setMaximumWidth(300);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 2);
    centerWindow();
}

HomeWidget::~HomeWidget()
{
    delete ui;
}

void HomeWidget::updateUIUsername(QString &username)
{
    ui->leftWidget->updateUIUsername(username);
}

void HomeWidget::updateUIUserCount(int userCount)
{
    ui->leftWidget->updateUIUserCount(userCount);
}

void HomeWidget::updateUIConnState(ConnState &state)
{
    ui->leftWidget->updateUIConnState(state);
}

void HomeWidget::addRoomIOMessage(QString &msg)
{
    ui->leftWidget->addRoomIOMessage(msg);
}

void HomeWidget::clearRoomIOMessageList()
{
    ui->leftWidget->clearRoomIOMessageList();
}

void HomeWidget::updateUIChatMsg(QString &sender, QString &contentStr, QString &timeStr)
{
    ui->rightWidget->updateUIChatMsg(sender, contentStr, timeStr);
}

void HomeWidget::clearRoomChatMsg()
{
    ui->rightWidget->clearRoomChatMsg();
}

void HomeWidget::centerWindow()
{
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    int x = (screenWidth - width()) / 2;
    int y = (screenHeight - height()) / 2;
    move(x, y);
}
