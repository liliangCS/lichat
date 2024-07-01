#include "homerightwidget.h"
#include "ui_homerightwidget.h"

HomeRightWidget::HomeRightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeRightWidget)
{
    ui->setupUi(this);
}

HomeRightWidget::~HomeRightWidget()
{
    delete ui;
}
