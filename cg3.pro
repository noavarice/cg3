#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T12:22:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cg3
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    conecoordsgen.cpp \
    vertex.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    conecoordsgen.h \
    vertex.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
