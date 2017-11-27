# Created by and for Qt Creator. This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = osces

HEADERS = \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/Apu.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/ApuRegisters.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/NoiseGenerator.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/SquareGenerator.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/TriangleGenerator.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/AoRom.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/CartridgeMapperTypes.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/IMapper.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/Mmc1.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/Mmc3.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/NoRom.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/UnRom.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Cartridge.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/GameRomAnaliser.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Control/Control.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cpu/Cpu.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cpu/CpuOpCodes.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Cpu/CpuRegisters.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Ppu/Ppu.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Ppu/PpuPalette.h \
   $$PWD/apps/nes_emulator/src/GameConsole/Ppu/PpuRegisters.h \
   $$PWD/apps/nes_emulator/src/GameConsole/GameConsole.h \
   $$PWD/apps/nes_emulator/src/Emulator.h \
   $$PWD/apps/nes_emulator/src/main.h \
   $$PWD/apps/snake/src/main.h \
   $$PWD/apps/snake/src/Snake.h \
   $$PWD/apps/snake/src/SnakeItem.h \
   $$PWD/core/crossplatform/System/Display/Display.h \
   $$PWD/core/crossplatform/System/Keyboard/CodePageTable.h \
   $$PWD/core/crossplatform/System/Keyboard/Keyboard.h \
   $$PWD/core/crossplatform/System/Keyboard/KeyCode.h \
   $$PWD/core/crossplatform/System/SysTimer/SysTimer.h \
   $$PWD/core/crossplatform/OscesFramework.h \
   $$PWD/core/include/GraphicalPrimitives/Line.h \
   $$PWD/core/include/GraphicalPrimitives/Surface.h \
   $$PWD/core/include/DisplayInterface.h \
   $$PWD/core/include/DisplayTypes.h \
   $$PWD/core/include/KeyboardInterface.h \
   $$PWD/core/include/KeyCode.h \
   $$PWD/core/include/NonCopyable.h \
   $$PWD/core/include/OscesFrameworkInterface.h \
   $$PWD/core/include/System.h \
   $$PWD/core/include/SysTimerInterface.h \
   $$PWD/core/include/ThreadInterface.h \
   $$PWD/core/platform/Host/System/Display/DisplayPlatform.h \
   $$PWD/core/platform/Host/System/Keyboard/KeyboardPlatform.h \
   $$PWD/core/platform/Host/System/SysTimer/SysTimerPlatform.h \
   $$PWD/core/platform/Host/System/OscesFramework.h \
   $$PWD/core/platform/OscesBoard/Drivers/DmaDriver.h \
   $$PWD/core/platform/OscesBoard/Drivers/FsmcDriver.h \
   $$PWD/core/platform/OscesBoard/Drivers/GpioDriver.h \
   $$PWD/core/platform/OscesBoard/Drivers/GpioTypes.h \
   $$PWD/core/platform/OscesBoard/Drivers/I2SDriver.h \
   $$PWD/core/platform/OscesBoard/Drivers/InterruptManager.h \
   $$PWD/core/platform/OscesBoard/Drivers/SdioDriver.h \
   $$PWD/core/platform/OscesBoard/Drivers/SysTimerDriver.h \
   $$PWD/core/platform/OscesBoard/Drivers/UDA1334_Driver.h \
   $$PWD/core/platform/OscesBoard/Drivers/VirtualPort.h \
   $$PWD/core/platform/OscesBoard/Drivers/VirtualPortTypes.h \
   $$PWD/core/platform/OscesBoard/Kernel/Context.h \
   $$PWD/core/platform/OscesBoard/Kernel/ContextSwitcher.h \
   $$PWD/core/platform/OscesBoard/Kernel/Kernel.h \
   $$PWD/core/platform/OscesBoard/Kernel/MemoryManager.h \
   $$PWD/core/platform/OscesBoard/Kernel/SchedulerPlatform.h \
   $$PWD/core/platform/OscesBoard/Kernel/ThreadPlatform.h \
   $$PWD/core/platform/OscesBoard/System/Buttons/buttons.h \
   $$PWD/core/platform/OscesBoard/System/ClockManager/ClockManager.h \
   $$PWD/core/platform/OscesBoard/System/Display/DisplayPlatform.h \
   $$PWD/core/platform/OscesBoard/System/ExtRam/ExtRam.h \
   $$PWD/core/platform/OscesBoard/System/FileSystem/fat32.h \
   $$PWD/core/platform/OscesBoard/System/FileSystem/FileSystem.h \
   $$PWD/core/platform/OscesBoard/System/FileSystem/ntfs.h \
   $$PWD/core/platform/OscesBoard/System/FileSystem/SdCardDriver.h \
   $$PWD/core/platform/OscesBoard/System/Keyboard/PS2KeyboardPlatform.h \
   $$PWD/core/platform/OscesBoard/System/Leds/leds.h \
   $$PWD/core/platform/OscesBoard/System/SysTimer/SysTimerPlatform.h \
   $$PWD/core/platform/OscesBoard/OscesFrameworkPlatform.h \
   $$PWD/thirdparty/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h \
   $$PWD/thirdparty/CMSIS/Device/ST/STM32F4xx/Include/system_stm32f4xx.h \
   $$PWD/thirdparty/CMSIS/Include/arm_common_tables.h \
   $$PWD/thirdparty/CMSIS/Include/arm_math.h \
   $$PWD/thirdparty/CMSIS/Include/core_cm0.h \
   $$PWD/thirdparty/CMSIS/Include/core_cm3.h \
   $$PWD/thirdparty/CMSIS/Include/core_cm4.h \
   $$PWD/thirdparty/CMSIS/Include/core_cm4_simd.h \
   $$PWD/thirdparty/CMSIS/Include/core_cmFunc.h \
   $$PWD/thirdparty/CMSIS/Include/core_cmInstr.h \
   $$PWD/thirdparty/CMSIS/Include/core_sc000.h \
   $$PWD/thirdparty/CMSIS/Include/core_sc300.h \
   $$PWD/thirdparty/MemTest/MemTest.h \
   $$PWD/thirdparty/SDL2-VC/include/begin_code.h \
   $$PWD/thirdparty/SDL2-VC/include/close_code.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_assert.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_atomic.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_audio.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_bits.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_blendmode.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_clipboard.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_config.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_cpuinfo.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_endian.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_error.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_events.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_filesystem.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_gamecontroller.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_gesture.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_haptic.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_hints.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_joystick.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_keyboard.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_keycode.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_loadso.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_log.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_main.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_messagebox.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_mouse.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_mutex.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_name.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_opengl.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_opengles.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_opengles2.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_pixels.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_platform.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_power.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_quit.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_rect.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_render.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_revision.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_rwops.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_scancode.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_shape.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_stdinc.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_surface.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_system.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_syswm.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_assert.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_common.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_compare.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_crc32.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_font.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_fuzzer.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_harness.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_images.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_log.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_md5.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_test_random.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_thread.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_timer.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_touch.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_types.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_version.h \
   $$PWD/thirdparty/SDL2-VC/include/SDL_video.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/misc.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_adc.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_can.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_crc.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_cryp.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dac.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dbgmcu.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dcmi.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_exti.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_flash.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fsmc.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_gpio.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_hash.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_i2c.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_iwdg.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_pwr.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rcc.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rng.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rtc.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sdio.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_spi.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_syscfg.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_tim.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_usart.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_wwdg.h \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/stm32f4xx_conf.h \
    core/include/osces.h \
    core/new/include/OscesDefs.h \
    core/new/include/Osces.h \
    core/new/include/NonCopyable.h \
    core/new/include/Screen.h \
    core/new/include/Painter.h \
    core/new/include/PlatformScreen.h

SOURCES = \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/Apu.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/ApuRegisters.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/NoiseGenerator.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/SquareGenerator.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Apu/TriangleGenerator.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/AoRom.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/IMapper.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/Mmc1.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/Mmc3.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/NoRom.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers/UnRom.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Cartridge.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/GameRomAnaliser.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Control/Control.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cpu/Cpu.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cpu/CpuOpCodes.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Cpu/CpuRegisters.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Ppu/Ppu.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Ppu/PpuPalette.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/Ppu/PpuRegisters.cpp \
   $$PWD/apps/nes_emulator/src/GameConsole/GameConsole.cpp \
   $$PWD/apps/nes_emulator/src/Games/Balloon_Fight.cpp \
   $$PWD/apps/nes_emulator/src/Emulator.cpp \
   $$PWD/apps/nes_emulator/src/main.cpp \
   $$PWD/apps/simulator/Simulator.cpp \
   $$PWD/apps/snake/src/main.cpp \
   $$PWD/apps/snake/src/Snake.cpp \
   $$PWD/apps/snake/src/SnakeItem.cpp \
   $$PWD/core/crossplatform/GraphicalPrimitives/Line.cpp \
   $$PWD/core/crossplatform/GraphicalPrimitives/Surface.cpp \
   $$PWD/core/crossplatform/System/Display/Display.cpp \
   $$PWD/core/crossplatform/System/Keyboard/Keyboard.cpp \
   $$PWD/core/crossplatform/System/SysTimer/SysTimer.cpp \
   $$PWD/core/platform/Host/System/Display/DisplayPlatform.cpp \
   $$PWD/core/platform/Host/System/Keyboard/KeyboardPlatform.cpp \
   $$PWD/core/platform/Host/System/SysTimer/SysTimerPlatform.cpp \
   $$PWD/core/platform/Host/System/OscesFramework.cpp \
   $$PWD/core/platform/OscesBoard/Drivers/DmaDriver.cpp \
   $$PWD/core/platform/OscesBoard/Drivers/FsmcDriver.cpp \
   $$PWD/core/platform/OscesBoard/Drivers/GpioDriver.cpp \
   $$PWD/core/platform/OscesBoard/Drivers/I2SDriver.cpp \
   $$PWD/core/platform/OscesBoard/Drivers/InterruptManager.cpp \
   $$PWD/core/platform/OscesBoard/Drivers/SdioDriver.cpp \
   $$PWD/core/platform/OscesBoard/Drivers/SysTimerDriver.cpp \
   $$PWD/core/platform/OscesBoard/Drivers/UDA1334_Driver.cpp \
   $$PWD/core/platform/OscesBoard/Drivers/VirtualPort.cpp \
   $$PWD/core/platform/OscesBoard/Kernel/Context.cpp \
   $$PWD/core/platform/OscesBoard/Kernel/ContextSwitcher.cpp \
   $$PWD/core/platform/OscesBoard/Kernel/Kernel.cpp \
   $$PWD/core/platform/OscesBoard/Kernel/MemoryManager.cpp \
   $$PWD/core/platform/OscesBoard/Kernel/SchedulerPlatform.cpp \
   $$PWD/core/platform/OscesBoard/Kernel/ThreadPlatform.cpp \
   $$PWD/core/platform/OscesBoard/System/Buttons/buttons.cpp \
   $$PWD/core/platform/OscesBoard/System/ClockManager/ClockManager.cpp \
   $$PWD/core/platform/OscesBoard/System/Display/DisplayPlatform.cpp \
   $$PWD/core/platform/OscesBoard/System/ExtRam/ExtRam.cpp \
   $$PWD/core/platform/OscesBoard/System/FileSystem/fat32.cpp \
   $$PWD/core/platform/OscesBoard/System/FileSystem/FileSystem.cpp \
   $$PWD/core/platform/OscesBoard/System/FileSystem/ntfs.cpp \
   $$PWD/core/platform/OscesBoard/System/FileSystem/SdCardDriver.cpp \
   $$PWD/core/platform/OscesBoard/System/Keyboard/PS2KeyboardPlatform.cpp \
   $$PWD/core/platform/OscesBoard/System/Leds/leds.cpp \
   $$PWD/core/platform/OscesBoard/System/SysTimer/SysTimerPlatform.cpp \
   $$PWD/core/platform/OscesBoard/OscesFrameworkPlatform.cpp \
   $$PWD/thirdparty/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c \
   $$PWD/thirdparty/MemTest/MemTest.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/misc.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
   $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c \
    core/new/include/Oscesces.cpp \
    core/new/include/Osces.cpp \
    core/new/include/Display.cpp \
    core/new/include/Screen.cpp \
    core/new/include/Painter.cpp \
    core/new/include/PlatformScreen.cpp

INCLUDEPATH = \
    $$PWD/apps/nes_emulator/src \
    $$PWD/apps/nes_emulator/src/GameConsole \
    $$PWD/apps/nes_emulator/src/GameConsole/Apu \
    $$PWD/apps/nes_emulator/src/GameConsole/Cartridge \
    $$PWD/apps/nes_emulator/src/GameConsole/Cartridge/Mappers \
    $$PWD/apps/nes_emulator/src/GameConsole/Control \
    $$PWD/apps/nes_emulator/src/GameConsole/Cpu \
    $$PWD/apps/nes_emulator/src/GameConsole/Ppu \
    $$PWD/apps/snake/src \
    $$PWD/core/crossplatform \
    $$PWD/core/crossplatform/System/Display \
    $$PWD/core/crossplatform/System/Keyboard \
    $$PWD/core/crossplatform/System/SysTimer \
    $$PWD/core/include \
    $$PWD/core/include/GraphicalPrimitives \
    $$PWD/core/platform/Host/System \
    $$PWD/core/platform/Host/System/Display \
    $$PWD/core/platform/Host/System/Keyboard \
    $$PWD/core/platform/Host/System/SysTimer \
    $$PWD/core/platform/OscesBoard \
    $$PWD/core/platform/OscesBoard/Drivers \
    $$PWD/core/platform/OscesBoard/Kernel \
    $$PWD/core/platform/OscesBoard/System/Buttons \
    $$PWD/core/platform/OscesBoard/System/ClockManager \
    $$PWD/core/platform/OscesBoard/System/Display \
    $$PWD/core/platform/OscesBoard/System/ExtRam \
    $$PWD/core/platform/OscesBoard/System/FileSystem \
    $$PWD/core/platform/OscesBoard/System/Keyboard \
    $$PWD/core/platform/OscesBoard/System/Leds \
    $$PWD/core/platform/OscesBoard/System/SysTimer \
    $$PWD/thirdparty/CMSIS/Device/ST/STM32F4xx/Include \
    $$PWD/thirdparty/CMSIS/Include \
    $$PWD/thirdparty/MemTest \
    $$PWD/thirdparty/SDL2-VC/include \
    $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver \
    $$PWD/thirdparty/STM32F4/STM32F4xx_StdPeriph_Driver/inc

#DEFINES = 

