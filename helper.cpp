#include "helper.h"

#include <QFile>
#include <QDebug>

Helper::Helper()
{

}

void Helper::loadStyleSheet(QWidget *widget, const QString &sheetName)
{
    QFile file(sheetName);
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        widget->setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Could not open stylesheet file";
    }
}
