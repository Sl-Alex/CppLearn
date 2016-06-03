QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = app

TARGET = books

SOURCES += main.cpp \
    book.cpp \
    mainwindow.cpp \
    booktablemodel.cpp \
    bookparser.cpp

HEADERS += \
    book.h \
    mainwindow.h \
    booktablemodel.h \
    bookparser.h

FORMS += \
    mainwindow.ui

