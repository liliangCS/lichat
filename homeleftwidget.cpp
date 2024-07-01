#include "homeleftwidget.h"
#include "ui_homeleftwidget.h"
#include "helper.h"

HomeLeftWidget::HomeLeftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeLeftWidget)
{
    ui->setupUi(this);
    Helper::loadStyleSheet(this, ":/qss/homeLeftWidget.qss");
}

HomeLeftWidget::~HomeLeftWidget()
{
    delete ui;
}
