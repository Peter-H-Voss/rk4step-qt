#-------------------------------------------------
#
# Project created by QtCreator 2012-09-20T15:09:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rk4krok
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rk41d.cpp \
    pot.cpp

HEADERS  += mainwindow.h \
    rk41d.h \
    pot.h

FORMS    += mainwindow.ui
