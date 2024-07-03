#include "homerightwidget.h"
#include "ui_homerightwidget.h"
#include "helper.h"
#include "chatroom.h"

HomeRightWidget::HomeRightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeRightWidget)
{
    ui->setupUi(this);
    Helper::loadStyleSheet(this, ":/qss/homeRightWidget.qss");

    //sendBtn
    connect(ui->sendBtn, &QPushButton::clicked, [this](){
        QString contentStr = ui->inputTextEdit->document()->toRawText();
        ChatRoom::getInstance()->sendPlainTextMsg(contentStr);
        ui->inputTextEdit->clear();
    });
}

HomeRightWidget::~HomeRightWidget()
{
    delete ui;
}

void HomeRightWidget::updateUIChatMsg(QString &sender, QString &contentStr, QString &timeStr)
{
    QString chatMsgStr = QString(R"(
                        <p>
                            <span style="color: #888">%1&nbsp;&nbsp;</span>
                            <span style="color: red">%2</span>
                            <span style="color: green">说：</span>
                            <span style="color: blue">%3</span>
                        </p>
                        <br />
                      )").arg(timeStr).arg(sender).arg(contentStr);
    ui->chatTextEdit->insertHtml(chatMsgStr);
}

void HomeRightWidget::clearRoomChatMsg()
{
    ui->chatTextEdit->clear();
}
