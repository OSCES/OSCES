#include "MemoryManager.h"
#include <string.h>

uint32_t AllocateThreadStack(uint32_t size)
{
   uint32_t *stack = new uint32_t[size];

   asm( "nop" );
   asm( "nop" );
   asm( "nop" );

   memset(stack, 0, size);

   return static_cast<uint32_t>(&stack[size - 8]);
}
