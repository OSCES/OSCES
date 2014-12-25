#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>


typedef void ( Routine_t )( void* pContextA, void* pContextB );

class Context_t
{
public:
    void SetNext( Context_t* pContext );
    void SaveStackPointer( uint32_t stackPointer );
    uint32_t RetrieveStackPointer();
    
    
    void SetRoutine( Routine_t* pRoutine );
    
private:
    uint32_t         m_StackPointer;
    Routine_t*       m_fpRoutine;
    uint32_t         ThreadRoutine;
//    ThreadTableItem* NextItem;

};




#endif // CONTEXT_SWITCHER_H
