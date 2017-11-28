#include "Cpu.h"
#include "Z80.h"


static Z80   m_Cpu;
static void* m_Context;

static BusWriteCallBack_t fp_BusWriteCallBack;
static BusReadCallBack_t  fp_BusReadCallBack;

static BusWriteCallBack_t fp_PortWriteCallBack;
static BusReadCallBack_t  fp_PortReadCallBack;
		
void Cpu_t::SetBusWriteCallBack( void* pContext, BusWriteCallBack_t busWriteCallBack )
{
    m_Context = pContext;
    fp_BusWriteCallBack = busWriteCallBack;
}

void Cpu_t::SetBusReadCallBack( void* pContext, BusReadCallBack_t busReadCallBack )
{
    m_Context = pContext;
    fp_BusReadCallBack = busReadCallBack;
}

void Cpu_t::SetPortWriteCallBack( void* pContext, BusWriteCallBack_t portWriteCallBack )
{
    m_Context = pContext;
    fp_PortWriteCallBack = portWriteCallBack;
}

void Cpu_t::SetPortReadCallBack( void* pContext, BusReadCallBack_t portReadCallBack )
{
    m_Context = pContext;
    fp_PortReadCallBack = portReadCallBack;
}



void Cpu_t::Reset( void ) 
{
    ResetZ80( &m_Cpu );
}

//void Cpu_t::NonMaskableInterrupt( void ) 
//{
//  
//}
//
//void Cpu_t::InterruptRequest( void) 
//{
//}    

uint8_t Cpu_t::Run( void )
{
    ExecZ80( &m_Cpu );
    return 0;
}

void WrZ80( uint16_t addr, uint8_t value )
{
    fp_BusWriteCallBack( m_Context, addr, value );
}

uint8_t RdZ80( word addr )
{
    return fp_BusReadCallBack( m_Context, addr );
}


void OutZ80( uint16_t port, uint8_t value)
{
    fp_PortWriteCallBack( m_Context, port, value );
}


byte InZ80( uint16_t port )
{
    return fp_PortReadCallBack( m_Context, port );
}

void PatchZ80( Z80 *R)
{
    int a = 0;
}

word LoopZ80( Z80 *R)
{
    int a = 0;

  return 0;
}



