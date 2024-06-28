#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include <QMouseEvent>
#include "helper.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);
    Helper::loadStyleSheet(this, ":/qss/loginDialog.qss");
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
