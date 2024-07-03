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
    void updateUIRoomIOMsg(QString &msg);

    void addRoomIOMessage(QString &msg);
    void clearRoomIOMessageList();
    QStringList* getRoomIOMessageList();

private:
    Ui::HomeLeftWidget *ui;

    QStringList *m_roomIOMessageList;

signals:
    void newRoomIOMessage(QString &msg);
};

#endif // HOMELEFTWIDGET_H
