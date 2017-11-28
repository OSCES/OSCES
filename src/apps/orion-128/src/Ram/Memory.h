#ifndef _Memory_h_
#define _Memory_h_

#include <stdint.h>

#define ORION_MEMORY_PAGES_CNT  4
#define ORION_MEMORY_SIZE_PAGE0 0xFFFF
#define ORION_MEMORY_SIZE_PAGE1 0xF000
#define ORION_MEMORY_SIZE_PAGE2 0xF000
#define ORION_MEMORY_SIZE_PAGE3 0xF000

#define ORION_BIOS_SIZE         2048
#define ORION_BIOS_START_ADDR   0xF800

enum MemoryPage_t
{
    ORION_MEMORY_PAGE0 = 0,
    ORION_MEMORY_PAGE1,
    ORION_MEMORY_PAGE2,
    ORION_MEMORY_PAGE3,
};

class Memory_t
{
    public:
        void Reset( void );
        void Erase( void );
        void SwitchPage( MemoryPage_t page );
        uint8_t* GetMemoryPointer( void );
        uint8_t* GetMemoryPointer( MemoryPage_t page );

    private:
        MemoryPage_t m_MemoryPage;

    private:
        uint8_t* m_pRamTable[ ORION_MEMORY_PAGES_CNT ];
        uint8_t* m_pMemory;      
};

#endif