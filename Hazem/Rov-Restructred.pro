#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T03:08:51
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rov-Restructred
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    joystick.cpp \
    joystick_handler.cpp \
    countdown.cpp

HEADERS  += mainwindow.h \
    joystick.h \
    joystick_handler.h \
    countdown.h

FORMS    += mainwindow.ui

LIBS += -LE:/SDL2/SDL2-2.0.8/lib/x86
LIBS += -lSDL2

INCLUDEPATH += E:/SDL2/SDL2-2.0.8/include
