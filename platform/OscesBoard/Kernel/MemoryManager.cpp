#include "MemoryManager.h"
#include <string.h>

uint32_t AllocateThreadStack( uint32_t size )
{
   uint32_t* pStack = new uint32_t[ size ];
  
   asm( "nop" );
   asm( "nop" );
   asm( "nop" );
   
   memset( pStack, 0, size );
   
   return ( uint32_t )&pStack[ size - 8 ];
}