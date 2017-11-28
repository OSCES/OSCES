HEADERS += \
    $$PWD/src/Emulator.h \
    $$PWD/src/GameConsole/Apu/Apu.h \
    $$PWD/src/GameConsole/Apu/ApuRegisters.h \
    $$PWD/src/GameConsole/Apu/NoiseGenerator.h \
    $$PWD/src/GameConsole/Apu/SquareGenerator.h \
    $$PWD/src/GameConsole/Apu/TriangleGenerator.h \
    $$PWD/src/GameConsole/Cartridge/Mappers/AoRom.h \
    $$PWD/src/GameConsole/Cartridge/Mappers/CartridgeMapperTypes.h \
    $$PWD/src/GameConsole/Cartridge/Mappers/IMapper.h \
    $$PWD/src/GameConsole/Cartridge/Mappers/Mmc1.h \
    $$PWD/src/GameConsole/Cartridge/Mappers/Mmc3.h \
    $$PWD/src/GameConsole/Cartridge/Mappers/NoRom.h \
    $$PWD/src/GameConsole/Cartridge/Mappers/UnRom.h \
    $$PWD/src/GameConsole/Cartridge/Cartridge.h \
    $$PWD/src/GameConsole/Cartridge/GameRomAnaliser.h \
    $$PWD/src/GameConsole/Control/Control.h \
    $$PWD/src/GameConsole/Cpu/Cpu.h \
    $$PWD/src/GameConsole/Cpu/CpuOpCodes.h \
    $$PWD/src/GameConsole/Cpu/CpuRegisters.h \
    $$PWD/src/GameConsole/Ppu/Ppu.h \
    $$PWD/src/GameConsole/Ppu/PpuPalette.h \
    $$PWD/src/GameConsole/Ppu/PpuRegisters.h \
    $$PWD/src/GameConsole/GameConsole.h \
    $$PWD/src/Games/BalloonFight.h \
    $$PWD/src/Games/BattleCity.h \
    $$PWD/src/Games/Contra.h \
    $$PWD/src/Games/SuperMario.h \
    $$PWD/src/Emulator.h

SOURCES += \
    $$PWD/src/GameConsole/Apu/Apu.cpp \
    $$PWD/src/GameConsole/Apu/ApuRegisters.cpp \
    $$PWD/src/GameConsole/Apu/NoiseGenerator.cpp \
    $$PWD/src/GameConsole/Apu/SquareGenerator.cpp \
    $$PWD/src/GameConsole/Apu/TriangleGenerator.cpp \
    $$PWD/src/GameConsole/Cartridge/Mappers/AoRom.cpp \
    $$PWD/src/GameConsole/Cartridge/Mappers/IMapper.cpp \
    $$PWD/src/GameConsole/Cartridge/Mappers/Mmc1.cpp \
    $$PWD/src/GameConsole/Cartridge/Mappers/Mmc3.cpp \
    $$PWD/src/GameConsole/Cartridge/Mappers/NoRom.cpp \
    $$PWD/src/GameConsole/Cartridge/Mappers/UnRom.cpp \
    $$PWD/src/GameConsole/Cartridge/Cartridge.cpp \
    $$PWD/src/GameConsole/Cartridge/GameRomAnaliser.cpp \
    $$PWD/src/GameConsole/Control/Control.cpp \
    $$PWD/src/GameConsole/Cpu/Cpu.cpp \
    $$PWD/src/GameConsole/Cpu/CpuOpCodes.cpp \
    $$PWD/src/GameConsole/Cpu/CpuRegisters.cpp \
    $$PWD/src/GameConsole/Ppu/Ppu.cpp \
    $$PWD/src/GameConsole/Ppu/PpuPalette.cpp \
    $$PWD/src/GameConsole/Ppu/PpuRegisters.cpp \
    $$PWD/src/GameConsole/GameConsole.cpp \
    $$PWD/src/Games/Rom.cpp \
    $$PWD/src/Emulator.cpp \
    $$PWD/src/EmulatorMain.cpp
