#ifndef HOMELEFTWIDGET_H
#define HOMELEFTWIDGET_H

#include <QWidget>

namespace Ui {
class HomeLeftWidget;
}

class HomeLeftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeLeftWidget(QWidget *parent = nullptr);
    ~HomeLeftWidget();

private:
    Ui::HomeLeftWidget *ui;
};

#endif // HOMELEFTWIDGET_H
