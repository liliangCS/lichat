#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QWidget>

struct IniConfig {
    QString server_ip;
    int server_port;
};

class Helper
{
public:
    Helper();

    static void loadStyleSheet(QWidget *widget, const QString &filePath);

    static IniConfig loadIniConfig();
};

#endif // HELPER_H
