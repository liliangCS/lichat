#ifndef HOMELEFTWIDGET_H
#define HOMELEFTWIDGET_H

#include <QWidget>
#include "websocketclient.h"

namespace Ui {
class HomeLeftWidget;
}

class HomeLeftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeLeftWidget(QWidget *parent = nullptr);
    ~HomeLeftWidget();

    void updateUIUsername(QString &username);
    void updateUIUserCount(int userCount);
    void updateUIConnState(ConnState &state);

private:
    Ui::HomeLeftWidget *ui;
};

#endif // HOMELEFTWIDGET_H
