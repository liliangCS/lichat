#include "homewidget.h"
#include "ui_homewidget.h"
#include <QDesktopWidget>
#include <QMouseEvent>
#include "helper.h"

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWidget)
{
    ui->setupUi(this);
    Helper::loadStyleSheet(this, ":/qss/homeWidget.qss");
    setWindowTitle("xxx聊天室");
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

void HomeWidget::centerWindow()
{
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    int x = (screenWidth - width()) / 2;
    int y = (screenHeight - height()) / 2;
    move(x, y);
}
