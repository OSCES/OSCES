#include "Context.h"
#include <string.h>
#include <intrinsics.h>

void Context_t::SaveStackPointer( uint32_t stackPointer )
{
    m_StackPointer = stackPointer;
}

void Context_t::SetRoutine( Routine_t* pRoutine )
{
    m_fpRoutine = pRoutine;
}

uint32_t Context_t::RetrieveStackPointer()
{
    return m_StackPointer;
}
    