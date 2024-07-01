#include "homerightwidget.h"
#include "ui_homerightwidget.h"
#include "helper.h"

HomeRightWidget::HomeRightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeRightWidget)
{
    ui->setupUi(this);
    Helper::loadStyleSheet(this, ":/qss/homeRightWidget.qss");
}

HomeRightWidget::~HomeRightWidget()
{
    delete ui;
}
