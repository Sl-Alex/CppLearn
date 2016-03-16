QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sharedpointer
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    mysharedpointer.h

