#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include "websocketclient.h"

namespace Ui {
class HomeWidget;
}

class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);
    ~HomeWidget();

    // homeLeftWidget
    void updateUIUsername(QString &username);
    void updateUIUserCount(int userCount);
    void updateUIConnState(ConnState &state);

    void addRoomIOMessage(QString &msg);

private:
    Ui::HomeWidget *ui;

    void centerWindow();
};

#endif // HOMEWIDGET_H
