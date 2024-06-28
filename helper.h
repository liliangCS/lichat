#ifndef HELPER_H
#define HELPER_H
#include <QString>
#include <QWidget>

class Helper
{
public:
    Helper();

    static void loadStyleSheet(QWidget *widget,  const QString &sheetName);
};

#endif // HELPER_H
