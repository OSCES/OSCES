QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = oscescore
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_NEEDS_QMAIN

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Uncomment for profiling with gprof
#CCFLAG += -pg
#QMAKE_CFLAGS = += -pg
#QMAKE_CXXFLAGS += -pg
#QMAKE_LFLAGS += -pg

DESTDIR = $$PWD/../../build/bin


INCLUDEPATH += $$PWD/include/
INCLUDEPATH += $$PWD/system/
INCLUDEPATH += $$PWD/system/buttons
INCLUDEPATH += $$PWD/system/clocks
INCLUDEPATH += $$PWD/system/fs
INCLUDEPATH += $$PWD/system/keyboard
INCLUDEPATH += $$PWD/system/leds
INCLUDEPATH += $$PWD/system/sound
INCLUDEPATH += $$PWD/system/systimer
INCLUDEPATH += $$PWD/system/video
INCLUDEPATH += $$PWD/drivers
INCLUDEPATH += $$PWD/drivers/audio
INCLUDEPATH += $$PWD/drivers/dma
INCLUDEPATH += $$PWD/drivers/fsmc
INCLUDEPATH += $$PWD/drivers/gpio
INCLUDEPATH += $$PWD/drivers/i2s
INCLUDEPATH += $$PWD/drivers/irq
INCLUDEPATH += $$PWD/drivers/rfm73
INCLUDEPATH += $$PWD/drivers/sdio
INCLUDEPATH += $$PWD/drivers/sysclock

HEADERS += \
    Simulator.h \
    system/keyboard/Keyboard.h \
    system/keyboard/KeyboardInterface.h \
    system/keyboard/KeyCode.h \
    system/video/AbstractDisplay.h \
    system/video/Color.h \
    system/video/Display.h \
    system/video/PaintEngine.h \
    system/video/VideoSystem.h \
    system/OscesCore.h \
    drivers/irq/InterruptManager.h \
    system/keyboard/PS2KeyboardPlatform.h

SOURCES += \
    main.cpp \
    Simulator.cpp \
    system/keyboard/Keyboard.cpp \
    system/video/AbstractDisplay.cpp \
    system/video/Color.cpp \
    system/video/Display.cpp \
    system/video/PaintEngine.cpp \
    system/video/VideoSystem.cpp \
    system/OscesCore.cpp \
    drivers/irq/InterruptManager.cpp \
    system/keyboard/PS2KeyboardPlatform.cpp

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
