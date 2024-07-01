#include "homeleftwidget.h"
#include "ui_homeleftwidget.h"

HomeLeftWidget::HomeLeftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeLeftWidget)
{
    ui->setupUi(this);
}

HomeLeftWidget::~HomeLeftWidget()
{
    delete ui;
}
