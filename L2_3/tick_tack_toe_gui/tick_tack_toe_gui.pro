QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = app

TARGET = books

SOURCES += main.cpp \
    abstractplayer.cpp \
    aiplayer.cpp \
    humanplayer.cpp \
    mainwindow.cpp \
    boardmodel.cpp

HEADERS += \
    abstractplayer.h \
    aiplayer.h \
    humanplayer.h \
    mainwindow.h \
    boardmodel.h


INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

FORMS += \
    mainwindow.ui
