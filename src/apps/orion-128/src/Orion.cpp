#include "Orion.h"
#include <stdio.h>

void Orion_t::PressKey( uint8_t scanCode )
{
    m_KeyBoard.PressKey( scanCode );
}

void Orion_t::UnPressKey( uint8_t scanCode )
{
    m_KeyBoard.UnPressKey( scanCode );
}

void Orion_t::SetPresentLineCallBack( void* pContext, PresentLineCallBack_t presentLineCallBack )
{
    m_Renderer.SetPresentLineCallBack( pContext, presentLineCallBack );
}
   
void Orion_t::Reset()
{   
    m_Memory.Reset();
  
    LoadBios("../../../bin/M1rk.bin");
    //LoadBios("../../../bin/ALMAZ-3.bru");

    //LoadBios("../../../bin/TEST256.BIN");
    

    m_Cpu.SetBusWriteCallBack ( this, CpuBusWrite );
    m_Cpu.SetBusReadCallBack  ( this, CpuBusRead  );
  
    m_Cpu.SetPortWriteCallBack( this, CpuPortWrite);
    m_Cpu.SetPortReadCallBack ( this, CpuBusRead  );
   
    m_KeyBoard.Init();

    m_Cpu.Reset();
}

void Orion_t::LoadBios( char* fileName )
{
    FILE * file = fopen( fileName, "rb" ); 
    
    uint8_t* pBios = new uint8_t [ ORION_BIOS_SIZE ];
   
    fread( pBios, sizeof( uint8_t ), ORION_BIOS_SIZE, file );
    
    uint8_t* memory = m_Memory.GetMemoryPointer();

    for( uint16_t idx = 0; idx != ORION_BIOS_SIZE; idx++ )
    {
        memory[ ORION_BIOS_START_ADDR + idx ] = pBios[ idx ]; 
        memory[ idx ] = pBios[ idx ]; 
    }
    
    delete pBios;
}

void Orion_t::RunFrame()
{
    for( uint32_t idx = 0; idx != ORION_CPU_CYCLES_PER_FRAME; idx ++ )
    {
        m_Cpu.Run(); 
    }

    m_Renderer.RunFrame( m_Memory.GetMemoryPointer( ORION_MEMORY_PAGE0 ), m_Memory.GetMemoryPointer( ORION_MEMORY_PAGE1 ) );
}

void Orion_t::CpuBusWrite( void* pContext, uint16_t addr, uint8_t value )
{
    Orion_t* pOrion = static_cast< Orion_t* >( pContext );


    if( ( addr >= ORION_PORT_BEGIN_ADDR ) && ( addr <= ORION_PORT_END_ADDR ) )
    {
        pOrion->PortWrite( addr, value );
    }
    else if( addr >= ORION_NON_SWITH_MEMMORY_ADDR )
    {
        pOrion->m_Memory.GetMemoryPointer( ORION_MEMORY_PAGE0 )[ addr ] = value;    
    }
    else
    {
        pOrion->m_Memory.GetMemoryPointer()[ addr ] = value;
    }
}

uint8_t Orion_t::CpuBusRead( void* pContext, uint16_t addr )
{
    Orion_t* pOrion = static_cast< Orion_t* >( pContext );

    uint8_t retValue = 0; 

    if( ( addr >= ORION_PORT_BEGIN_ADDR ) && ( addr <= ORION_PORT_END_ADDR ) )
    {
        retValue = pOrion->PortRead( addr );
    }
    else if( addr >= ORION_NON_SWITH_MEMMORY_ADDR )
    {
        retValue = pOrion->m_Memory.GetMemoryPointer( ORION_MEMORY_PAGE0 )[addr];    
    }
    else
    {
        retValue = pOrion->m_Memory.GetMemoryPointer()[addr];
    }

    return retValue;
}

void Orion_t::CpuPortWrite( void* pContext, uint16_t addr, uint8_t value )
{
    Orion_t* pOrion = static_cast< Orion_t* >( pContext );
    pOrion->PortWrite( addr << 8, value );
}


uint8_t Orion_t::CpuPortRead( void* pContext, uint16_t addr )
{
    Orion_t* pOrion = static_cast< Orion_t* >( pContext );
    return pOrion->PortRead( addr << 8 );
}


//#define ORION_KEYBOARD_PORT_ADDR     0xF400
//#define ORION_USER_PORT1_ADDR        0xF500
//#define ORION_USER_PORT2_ADDR        0xF600
//#define ORION_EXT_BOARD_PORT_ADDR    0xF700



// ------------------ PORTS -----------------------
void Orion_t::PortWrite( uint16_t port, uint8_t value )
{
    uint16_t ioPort = port & 0xFF00;

     uint8_t a = 0;

    switch ( ioPort )
    {
        case ORION_KEYBOARD_PORT_ADDR:
            m_KeyBoard.Write( port, value );
        break;
    
        case ORION_SYS_PORT1_ADDR:
            m_Renderer.SetVideoMode( value );
        break;
    
        case ORION_SYS_PORT2_ADDR:
            m_Memory.SwitchPage( ( MemoryPage_t )value );
        break;

        case ORION_SYS_PORT3_ADDR:
            m_Renderer.SwitchDisplay( value );
        break;

        case ORION_SYS_PORT4_ADDR:
            a = 0;
        break;

        default:
            a = 0;
        break;
    }

}

uint8_t i = 0;

uint8_t Orion_t::PortRead ( uint16_t port )
{
    uint16_t ioPort = port & 0xFF00;

    uint8_t retValue = 0; 

    uint8_t a = 0;

    switch ( ioPort )
    {
        case ORION_KEYBOARD_PORT_ADDR:
            retValue = m_KeyBoard.Read( port );
        break;
    
        case ORION_SYS_PORT1_ADDR:
            a = 0;
        break;
    
        case ORION_SYS_PORT2_ADDR:
            a = 0;
        break;

        case ORION_SYS_PORT3_ADDR:
            a = 0;
        break;

        case ORION_SYS_PORT4_ADDR:
            a = 0;
        break;

        default:
            a = 0;
        break;
    }

    return retValue;
}

// ------------------------------------------------



