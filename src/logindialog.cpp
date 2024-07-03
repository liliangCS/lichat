#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QMessageBox>

#include "include/logindialog.h"
#include "ui_logindialog.h"
#include "include/helper.h"
#include "include/websocketclient.h"
#include "include/chatroom.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/images/logo.ico"));
    setAttribute(Qt::WA_TranslucentBackground);
    Helper::loadStyleSheet(this, ":/qss/loginDialog.qss");

    //set box-shadow
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setColor(QColor("#666"));
    this->setGraphicsEffect(shadowEffect);
    this->setContentsMargins(2,2,2,2);

    //closeBtn
    connect(ui->closeBtn, &QPushButton::clicked, this, [this](){
        this->close();
    });

    //logoLabel
    QPixmap logoPixmap(":/images/logo.png");
    logoPixmap = logoPixmap.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->logoLabel->setPixmap(logoPixmap);

    //enterBtn
    ui->enterBtn->setFixedWidth(100);
    connect(ui->enterBtn, &QPushButton::clicked, this, [this](){
        if (ui->agreementCheckBox->checkState() == Qt::Unchecked)
        {
            QMessageBox::information(this, "提示", "请先阅读并同意《服务协议》");
            return;
        }

        if (ui->usernameLineEdit->text().trimmed() == "")
        {
            QMessageBox::information(this, "提示", "用户名不能为空");
            return;
        }

        if (WebSocketClient::getInstance()->getConnState() == ConnState::DISCONNECTED) {
            QMessageBox::information(this, "提示", "与服务器的连接断开，请检查服务器环境");
            return;
        }

        QString username = ui->usernameLineEdit->text().trimmed();

        ChatRoom::getInstance()->enterRoom(username);
    });
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}
