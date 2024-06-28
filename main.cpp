#include <QApplication>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog loginDialog;

    loginDialog.show();

    return a.exec();
}
