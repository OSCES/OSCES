#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/534592722/Cpu.o \
	${OBJECTDIR}/_ext/425842872/Display.o \
	${OBJECTDIR}/_ext/127121919/KeyBoard.o \
	${OBJECTDIR}/_ext/1386528437/Orion.o \
	${OBJECTDIR}/_ext/534580241/Ppi.o \
	${OBJECTDIR}/_ext/534578780/Memory.o \
	${OBJECTDIR}/_ext/1096154371/Renderer.o \
	${OBJECTDIR}/_ext/1386528437/main.o \
	${OBJECTDIR}/_ext/1222734031/Z80.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-O3 -Wstrict-aliasing
CXXFLAGS=-O3 -Wstrict-aliasing

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/../../../../build/Linux/Release/emulator

${CND_DISTDIR}/../../../../build/Linux/Release/emulator: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/../../../../build/Linux/Release
	${LINK.cc} -o ${CND_DISTDIR}/../../../../build/Linux/Release/emulator ${OBJECTFILES} ${LDLIBSOPTIONS} -lSDL2

${OBJECTDIR}/_ext/534592722/Cpu.o: ../../../src/Cpu/Cpu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534592722
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../thirdparty/SDL2-VC/include -I../../../thirdparty/Z80 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534592722/Cpu.o ../../../src/Cpu/Cpu.cpp

${OBJECTDIR}/_ext/425842872/Display.o: ../../../src/Display/Display.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/425842872
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../thirdparty/SDL2-VC/include -I../../../thirdparty/Z80 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/425842872/Display.o ../../../src/Display/Display.cpp

${OBJECTDIR}/_ext/127121919/KeyBoard.o: ../../../src/KeyBoard/KeyBoard.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/127121919
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../thirdparty/SDL2-VC/include -I../../../thirdparty/Z80 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/127121919/KeyBoard.o ../../../src/KeyBoard/KeyBoard.cpp

${OBJECTDIR}/_ext/1386528437/Orion.o: ../../../src/Orion.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../thirdparty/SDL2-VC/include -I../../../thirdparty/Z80 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/Orion.o ../../../src/Orion.cpp

${OBJECTDIR}/_ext/534580241/Ppi.o: ../../../src/Ppi/Ppi.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534580241
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../thirdparty/SDL2-VC/include -I../../../thirdparty/Z80 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534580241/Ppi.o ../../../src/Ppi/Ppi.cpp

${OBJECTDIR}/_ext/534578780/Memory.o: ../../../src/Ram/Memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534578780
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../thirdparty/SDL2-VC/include -I../../../thirdparty/Z80 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534578780/Memory.o ../../../src/Ram/Memory.cpp

${OBJECTDIR}/_ext/1096154371/Renderer.o: ../../../src/Renderer/Renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1096154371
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../thirdparty/SDL2-VC/include -I../../../thirdparty/Z80 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1096154371/Renderer.o ../../../src/Renderer/Renderer.cpp

${OBJECTDIR}/_ext/1386528437/main.o: ../../../src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../thirdparty/SDL2-VC/include -I../../../thirdparty/Z80 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/main.o ../../../src/main.cpp

${OBJECTDIR}/_ext/1222734031/Z80.o: ../../../thirdparty/Z80/Z80.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1222734031
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../thirdparty/SDL2-VC/include -I../../../thirdparty/Z80 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1222734031/Z80.o ../../../thirdparty/Z80/Z80.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/../../../../build/Linux/Release/emulator

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
