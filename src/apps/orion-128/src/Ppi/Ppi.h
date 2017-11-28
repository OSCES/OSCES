#ifndef _Ppi_h_
#define _Ppi_h_

#include <stdint.h>


#define PPI_CONTROL_REG_BSR_MODE 0
#define PPI_CONTROL_REG_IO_MODE  1


#define PPI_GROUP_MODE_BASIC_INOUT       0
#define PPI_GROUP_MODE_STROBED_INOUT     1
#define PPI_GROUP_MODE_BIDIR_BUS         2



enum PpiPortAddr_t
{
    PPI_ADDR_PORTA = 0,
    PPI_ADDR_PORTB    ,
    PPI_ADDR_PORTC    ,
    PPI_ADDR_CTRL     ,
};

struct PpiControlBsrReg_t
{
    uint8_t SetBit      : 1;
    uint8_t BitSelPortC : 3;
    uint8_t DoNotCare   : 3;
    uint8_t Mode        : 1;  
};


struct PpiControlIoReg_t
{
    uint8_t GroupB_DirectionPortC : 1; //Lower
    uint8_t GroupB_DirectionPortB : 1;
    uint8_t GroupB_Mode           : 1;
    
    uint8_t GroupA_DirectionPortC : 1; //Upper
    uint8_t GroupA_DirectionPortA : 1;
    
    uint8_t GroupA_Mode           : 2;
    
    uint8_t Mode                  : 1;  
};


struct PpiControlModeReg_t
{
    uint8_t             : 7;
    uint8_t Mode        : 1;  
};



union PpiControlReg_t
{
    PpiControlBsrReg_t  Bsr;
    PpiControlIoReg_t   Io;
    PpiControlModeReg_t Mode;
	uint8_t             Value;
};

typedef void    (*PpiPortWriteCallBack_t) ( void* pContext, PpiPortAddr_t port, uint8_t busData );
typedef uint8_t (*PpiPortReadCallBack_t ) ( void* pContext, PpiPortAddr_t port );


class Ppi_t
{
    public:
         
          void SetPortWriteCallBack( void* pContext, PpiPortWriteCallBack_t busWriteCallBack );
          void SetPortReadCallBack ( void* pContext, PpiPortReadCallBack_t busReadCallBack );



          void Write( PpiPortAddr_t addr, uint8_t data );
          uint8_t Read( PpiPortAddr_t addr/*, uint8_t data*/ );


    private:
          void WritePortA     ( uint8_t data );
          void WritePortB     ( uint8_t data );
          void WritePortC     ( uint8_t data );
          void WriteControlReg( uint8_t data );


          uint8_t ReadPortA( void );
          uint8_t ReadPortB( void );
          uint8_t ReadPortC( void );



          void WriteControlRegIoMode ( PpiControlIoReg_t  reg );
          void WriteControlRegRsrMode( PpiControlBsrReg_t reg );

    private:
          PpiControlIoReg_t  m_ControlIoReg;
          PpiControlBsrReg_t m_ControlBsrReg;

          PpiPortWriteCallBack_t  fp_PortWriteCallBack;
          PpiPortReadCallBack_t   fp_PortReadCallBack;
          void*                   m_pContext;
};

#endif