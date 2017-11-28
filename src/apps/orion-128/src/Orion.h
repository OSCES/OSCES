#ifndef _Orion_h_
#define _Orion_h_

#include <stdint.h>
#include "Cpu/Cpu.h"
#include "Ram/Memory.h"
#include "Renderer/Renderer.h"
#include "KeyBoard/KeyBoard.h"


#define ORION_NON_SWITH_MEMMORY_ADDR 0xF000
#define ORION_CPU_CYCLES_PER_FRAME   5000


// ------------------- PORTS ----------------------

#define ORION_PORT_BEGIN_ADDR 0xF400
#define ORION_PORT_END_ADDR   0xF800

#define ORION_KEYBOARD_PORT_ADDR     0xF400
#define ORION_USER_PORT1_ADDR        0xF500
#define ORION_USER_PORT2_ADDR        0xF600
#define ORION_EXT_BOARD_PORT_ADDR    0xF700

#define ORION_SYS_PORT1_ADDR         0xF800
#define ORION_SYS_PORT2_ADDR         0xF900
#define ORION_SYS_PORT3_ADDR         0xFA00
#define ORION_SYS_PORT4_ADDR         0xFB00
// ------------------------------------------------

class Orion_t
{
    public:
       void SetPresentLineCallBack( void* pContext, PresentLineCallBack_t presentLineCallBack );
       void Reset();
       void RunFrame();
	   void PressKey  ( uint8_t scanCode );
	   void UnPressKey( uint8_t scanCode );

    private:
       void LoadBios( char* fileName );

       void PortWrite( uint16_t port, uint8_t value );
       uint8_t PortRead ( uint16_t port );

    // ----------------- PORTS ---------------------
    private:
       

    private:
        static void CpuBusWrite( void* pContext, uint16_t addr, uint8_t value );
        static uint8_t CpuBusRead( void* pContext, uint16_t addr );
        
        static void CpuPortWrite( void* pContext, uint16_t addr, uint8_t value );
        static uint8_t CpuPortRead( void* pContext, uint16_t addr );
        

    private:
        Cpu_t      m_Cpu;
        Memory_t   m_Memory;
        Renderer_t m_Renderer;
        KeyBoard_t m_KeyBoard;
};  

#endif