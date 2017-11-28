#ifndef _Cpu_h_
#define _Cpu_h_

#include <stdint.h>


typedef void (*BusWriteCallBack_t)   ( void* pContext, uint16_t busAddr, uint8_t busData );
typedef uint8_t (*BusReadCallBack_t) ( void* pContext, uint16_t busAddr );

class Cpu_t
{
    public:      

		void SetBusWriteCallBack ( void* pContext, BusWriteCallBack_t busWriteCallBack );
		void SetBusReadCallBack  ( void* pContext, BusReadCallBack_t busReadCallBack );

        void SetPortWriteCallBack( void* pContext, BusWriteCallBack_t portWriteCallBack );
		void SetPortReadCallBack ( void* pContext, BusReadCallBack_t portReadCallBack );


    public:
      // -------- Interrupts ------------
        void Reset(void);
       // void NonMaskableInterrupt(void);
       // void InterruptRequest(void);
      //---------------------------------
    
        uint8_t Run(void);

};

#endif


