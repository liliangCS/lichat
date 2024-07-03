#include <QFile>
#include <QDebug>
#include "include/helper.h"

Helper::Helper()
{

}

void Helper::loadStyleSheet(QWidget *widget, const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QString::fromUtf8(file.readAll());
        widget->setStyleSheet(styleSheet);
        file.close();
    }
    else
    {
        qDebug() << "打开样式文件失败";
    }
}
