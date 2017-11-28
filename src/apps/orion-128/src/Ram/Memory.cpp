#include "Memory.h"
#include <memory.h>

void Memory_t::Reset( void )
{
    m_pRamTable[ ORION_MEMORY_PAGE0 ] = new uint8_t [ ORION_MEMORY_SIZE_PAGE0 ];
    m_pRamTable[ ORION_MEMORY_PAGE1 ] = new uint8_t [ ORION_MEMORY_SIZE_PAGE1 ];
    m_pRamTable[ ORION_MEMORY_PAGE2 ] = new uint8_t [ ORION_MEMORY_SIZE_PAGE2 ];
    m_pRamTable[ ORION_MEMORY_PAGE3 ] = new uint8_t [ ORION_MEMORY_SIZE_PAGE3 ];

    SwitchPage( ORION_MEMORY_PAGE0 );
    Erase();
 }

uint8_t* Memory_t::GetMemoryPointer( void )
{
    return m_pMemory;
}

uint8_t* Memory_t::GetMemoryPointer( MemoryPage_t page )
{
    return m_pRamTable[ page ];
}

void Memory_t::Erase( void )
{
    memset( m_pRamTable[ ORION_MEMORY_PAGE0 ], 0, ORION_MEMORY_SIZE_PAGE0 );
    memset( m_pRamTable[ ORION_MEMORY_PAGE1 ], 0, ORION_MEMORY_SIZE_PAGE1 );
    memset( m_pRamTable[ ORION_MEMORY_PAGE2 ], 0, ORION_MEMORY_SIZE_PAGE2 );
    memset( m_pRamTable[ ORION_MEMORY_PAGE3 ], 0, ORION_MEMORY_SIZE_PAGE3 );
}

void Memory_t::SwitchPage( MemoryPage_t page )
{
    m_MemoryPage = page;
    m_pMemory    = m_pRamTable[ m_MemoryPage ];
}
