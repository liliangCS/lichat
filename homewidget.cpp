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
    setMinimumSize(600, 400);
    Helper::loadStyleSheet(this, ":/qss/homeWidget.qss");
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