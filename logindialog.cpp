#include "logindialog.h"
#include "ui_logindialog.h"
#include "helper.h"

#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
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
    connect(ui->enterBtn, &QPushButton::clicked, this, [](){
        qDebug() << "enterBtn";
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
