#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>
#include <QMessageBox>
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

IniConfig Helper::loadIniConfig()
{
    QString configPath = QString("%1/lichat.config.ini").arg(QCoreApplication::applicationDirPath());
    QFile file(configPath);
    if (!file.exists()) {
        QMessageBox::information(nullptr, "提示", "没有找到配置文件");
    }
    QSettings settings(configPath, QSettings::IniFormat);
    IniConfig config;
    config.server_ip = settings.value("/server/ip").toString();
    config.server_port = settings.value("/server/port").toInt();

    qDebug() << config.server_ip;
    qDebug() << config.server_port;
    return config;
}
