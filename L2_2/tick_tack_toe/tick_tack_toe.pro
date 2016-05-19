TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board.cpp \
    abstractplayer.cpp \
    aiplayer.cpp \
    humanplayer.cpp \
    display.cpp

HEADERS += \
    board.h \
    abstractplayer.h \
    aiplayer.h \
    humanplayer.h \
    display.h


win32: LIBS += -L$$PWD/./ -lpdcurses

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./pdcurses.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/./libpdcurses.a
