QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 \
#          debug \
          release

#debug: {
#    QMAKE_POST_LINK += $$quote(cp $$PWD/lichat.config.ini $$OUT_PWD/lichat.config.ini)
#}

release: {
    QMAKE_POST_LINK += $$quote(cp $$PWD/lichat.config.ini $$OUT_PWD/lichat.config.ini)
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/chatroom.cpp \
    src/emojibtn.cpp \
    src/emojipickerdialog.cpp \
    src/helper.cpp \
    src/homeleftwidget.cpp \
    src/homerightwidget.cpp \
    src/homewidget.cpp \
    src/logindialog.cpp \
    main.cpp \
    src/websocketclient.cpp

HEADERS += \
    include/chatroom.h \
    include/emojibtn.h \
    include/emojipickerdialog.h \
    include/helper.h \
    include/homeleftwidget.h \
    include/homerightwidget.h \
    include/homewidget.h \
    include/logindialog.h \
    include/websocketclient.h

FORMS += \
    ui/emojipickerdialog.ui \
    ui/homeleftwidget.ui \
    ui/homerightwidget.ui \
    ui/homewidget.ui \
    ui/logindialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    lichat.config.ini

RC_ICONS = images/logo.ico
