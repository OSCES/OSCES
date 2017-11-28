#include "Ppi.h"

void Ppi_t::SetPortWriteCallBack( void* pContext, PpiPortWriteCallBack_t busWriteCallBack )
{
    fp_PortWriteCallBack = busWriteCallBack;
    m_pContext = pContext;
}


void Ppi_t::SetPortReadCallBack ( void* pContext, PpiPortReadCallBack_t busReadCallBack )
{
    fp_PortReadCallBack = busReadCallBack;
    m_pContext = pContext;
}


void Ppi_t::Write( PpiPortAddr_t addr, uint8_t data )
{
    void ( Ppi_t::* fp_WritePort[] )( uint8_t data ) = 
    { 
        &Ppi_t::WritePortA, 
        &Ppi_t::WritePortB,
        &Ppi_t::WritePortC,
        &Ppi_t::WriteControlReg
    };

    //fp_WritePort_t fp_WritePort[2];

    //fp_WritePort[0] = &Ppi_t::WritePortA;

   // ( this->*fp_WritePort[0] )( 0 );

    switch( addr )
    {
        case PPI_ADDR_PORTA:
            WritePortA( data );
        break;
    
        case PPI_ADDR_PORTB:
            WritePortB( data );
        break;
    
        case PPI_ADDR_PORTC:
            WritePortC( data );
        break;
    
        case PPI_ADDR_CTRL:
            WriteControlReg( data );
        break;
    
        default: break;
    };

}

uint8_t Ppi_t::Read( PpiPortAddr_t addr/*, uint8_t data*/ )
{
    uint8_t retValue = 0;

    switch( addr )
    {
        case PPI_ADDR_PORTA:
            retValue = ReadPortA();
        break;
    
        case PPI_ADDR_PORTB:
            retValue = ReadPortB();
        break;
    
        case PPI_ADDR_PORTC:
            retValue = ReadPortC();
        break;
        
        default: break;
    };

    return retValue;
}

void Ppi_t::WritePortA( uint8_t data )
{
    fp_PortWriteCallBack( m_pContext, PPI_ADDR_PORTA, data );
}

void Ppi_t::WritePortB( uint8_t data )
{
    fp_PortWriteCallBack( m_pContext, PPI_ADDR_PORTB, data );
}

void Ppi_t::WritePortC( uint8_t data )
{
    fp_PortWriteCallBack( m_pContext, PPI_ADDR_PORTC, data );
}

uint8_t Ppi_t::ReadPortA( void )
{
    return fp_PortReadCallBack( m_pContext, PPI_ADDR_PORTA );
}

uint8_t Ppi_t::ReadPortB( void )
{
    return fp_PortReadCallBack( m_pContext, PPI_ADDR_PORTB );
}

uint8_t Ppi_t::ReadPortC( void )
{
    return fp_PortReadCallBack( m_pContext, PPI_ADDR_PORTC );
}


void Ppi_t::WriteControlReg( uint8_t data )
{
    PpiControlReg_t ppiControlReg;
   
    ppiControlReg.Value = data;

    if( PPI_CONTROL_REG_IO_MODE == ppiControlReg.Mode.Mode )
    {
        WriteControlRegIoMode( ppiControlReg.Io );
    }
    else if( PPI_CONTROL_REG_BSR_MODE == ppiControlReg.Mode.Mode )
    {
        WriteControlRegRsrMode( ppiControlReg.Bsr );
    }
}

void Ppi_t::WriteControlRegIoMode ( PpiControlIoReg_t reg )
{
    m_ControlIoReg = reg;
}


void Ppi_t::WriteControlRegRsrMode( PpiControlBsrReg_t reg )
{
    m_ControlBsrReg = reg;
}
