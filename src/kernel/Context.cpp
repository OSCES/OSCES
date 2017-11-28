#include "Context.h"
#include <string.h>
#include <intrinsics.h>

void Context::setNext(Context *context)
{
}

void Context::saveStackPointer(uint32_t stackPointer)
{
    m_stackPointer = stackPointer;
}

void Context::setRoutine(Routine routine)
{
    if (m_routine == routine)
        return;

    m_routine = routine;
}

uint32_t Context::retrieveStackPointer()
{
    return m_stackPointer;
}
