#-------------------------------------------------
#
# Project created by QtCreator 2018-11-02T09:32:33
#
#-------------------------------------------------

QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ROV-Restructured
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0
PKGCONFIG += Qt5GLib-2.0 Qt5GStreamer-1.0 Qt5GStreamerUi-1.0 Qt5GStreamerUtils-1.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    countdown.cpp \
    gui.cpp \
    joystick.cpp \
    joystick_handler.cpp \
    tcpserver.cpp \
    gstream.cpp \
    buttonsconfiguration.cpp


HEADERS += \
        mainwindow.h \
    countdown.h \
    gui.h \
    joystick.h \
    joystick_handler.h \
    tcpserver.h \
    gstream.h \
    buttonsconfiguration.h

FORMS += \
        mainwindow.ui

LIBS += -L/usr/local/lib -lSDL2
INCLUDEPATH += /usr/local/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
