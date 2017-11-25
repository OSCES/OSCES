#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>


typedef void (*Routine)(void *contextA, void *contextB);

class Context
{
public:
    void setNext(Context *context);
    void saveStackPointer(uint32_t stackPointer);
    uint32_t retrieveStackPointer();

    void setRoutine(Routine routine);

private:
    Routine m_routine;
    uint32_t m_stackPointer;
    uint32_t m_threadRoutine;
//    ThreadTableItem *NextItem;
};




#endif // CONTEXT_SWITCHER_H
