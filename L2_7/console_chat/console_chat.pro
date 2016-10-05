TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32: LIBS += -L$$PWD/./ -lpdcurses -lws2_32

SOURCES += main.cpp \
    chatserver.cpp \
    chatconnection.cpp \
    connectionmanager.cpp \
    stringqueue.cpp

HEADERS += \
    chatserver.h \
    chatconnection.h \
    connectionmanager.h \
    stringqueue.h
