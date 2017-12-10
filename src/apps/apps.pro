QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = osces
TEMPLATE = app

DEFINES += NEEDS_OSCES_MAIN
CONFIG += raycasting

DESTDIR = $$PWD/../../build/bin

LIBS += -L$$PWD/../../build/bin/
LIBS += -loscescore

include($$PWD/include.pri)

nes {
include($$PWD/nes_emulator/nes.pri)
}

snake {
include($$PWD/snake/snake.pri)
}

orion {
include($$PWD/orion-128/orion-128.pri)
}

raycasting {
include($$PWD/raycasting/raycasting.pri)
}
