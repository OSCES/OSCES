INCLUDEPATH += $$PWD/thirdparty/Z80/

HEADERS += \
    $$PWD/src/Cpu/Cpu.h \
    $$PWD/src/KeyBoard/KeyBoard.h \
    $$PWD/src/Ppi/Ppi.h \
    $$PWD/src/Ram/Memory.h \
    $$PWD/src/Renderer/Renderer.h \
    $$PWD/src/Orion.h \
    $$PWD/thirdparty/Z80/Codes.h \
    $$PWD/thirdparty/Z80/CodesCB.h \
    $$PWD/thirdparty/Z80/CodesED.h \
    $$PWD/thirdparty/Z80/CodesXCB.h \
    $$PWD/thirdparty/Z80/CodesXX.h \
    $$PWD/thirdparty/Z80/Tables.h \
    $$PWD/thirdparty/Z80/Z80.h

SOURCES += \
    $$PWD/src/Cpu/Cpu.cpp \
    $$PWD/src/Ppi/Ppi.cpp \
    $$PWD/src/Ram/Memory.cpp \
    $$PWD/src/Renderer/Renderer.cpp \
    $$PWD/src/Orion.cpp \
    $$PWD/thirdparty/Z80/Z80.cpp \
    $$PWD/thirdparty/Z80/dasm.c \
    $$PWD/thirdparty/Z80/Debug.c \
    $$PWD/src/OrionMain.cpp \
    $$PWD/src/KeyBoard/O_KeyBoard.cpp
