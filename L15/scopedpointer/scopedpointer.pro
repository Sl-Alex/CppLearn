QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scopedpointer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myscopedpointer.cpp

HEADERS += \
    myscopedpointer.h

