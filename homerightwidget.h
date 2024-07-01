#ifndef HOMERIGHTWIDGET_H
#define HOMERIGHTWIDGET_H

#include <QWidget>

namespace Ui {
class HomeRightWidget;
}

class HomeRightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeRightWidget(QWidget *parent = nullptr);
    ~HomeRightWidget();

private:
    Ui::HomeRightWidget *ui;
};

#endif // HOMERIGHTWIDGET_H
