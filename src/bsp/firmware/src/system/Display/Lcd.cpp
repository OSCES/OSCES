
#include<stm32f2xx_rcc.h>

#include "Lcd.h"
#include "LcdTypes.h"

Lcd_t::Lcd_t()
{
    m_VoltageBus = new VirtualPort_t(VOLTAGE_BUS);
    m_DataBus    = new VirtualPort_t(DATA_BUS);

    m_RSpin = new GpioPin_t( PORTE, PIN_3 );
    m_RDpin = new GpioPin_t( PORTF, PIN_8 );
    m_WRpin = new GpioPin_t( PORTE, PIN_2 );
    m_DCpin = new GpioPin_t( PORTF, PIN_7 );

    m_RSpin->MakeOut();
    m_RDpin->MakeOut();
    m_WRpin->MakeOut();
    m_DCpin->MakeOut();
}

Lcd_t::~Lcd_t()
{
    HwEnable( false );
    
    delete m_VoltageBus;
    delete m_DataBus;

    delete m_RSpin;
    delete m_RDpin;
    delete m_WRpin;
    delete m_DCpin;
}

void Lcd_t::Init()
{
    HwEnable( true );
    SwReset();

    SendCommand( SLPOUT );
    SendCommand( DISPON );

    SendCommand( DISPON );
    Delay( 10 );

    SendCommand( MADCTR );
    SendData( 0xC0 );
    SendCommand( COLMOD );
    SendData( 0x07 );
}

void Lcd_t::Clear(Color_t color)
{
    SendCommand( CASET );
    SendData( 0 );
    SendData( 0 );   // x1

    SendData( 0 );
    SendData( 240 ); // x2

    SendCommand( RASET );
    SendData( 0 );
    SendData( 0 );   // y1
    SendData( 1 );
    SendData( 64 );  // y2

    SendCommand( RAMWR );
    for ( uint32_t i = 0; i < 76800 ; i++ )
    {
        SendData( color.r );
        SendData( color.g );
        SendData( color.b );
    }
}

void Lcd_t::SendCommand(LcdCommand_t command)
{
    m_DCpin->Clear();
    m_DataBus->Write(command);
    m_WRpin->Clear();
    m_DCpin->Set();
    m_WRpin->Set();
}

void Lcd_t::SendData(uint32_t data)
{
    m_DataBus->Write(data);
    m_WRpin->Clear();
    m_WRpin->Set();
}

void Lcd_t::HwEnable(bool enable)
{
    if( enable )
    {
        m_VoltageBus->Write(0x03);
    }
    else
    {
        m_VoltageBus->Write(0x00);
    }
}

void Lcd_t::SwReset()
{
    m_WRpin->Set();
    m_RSpin->Clear();
    Delay( 10 );
    m_RSpin->Set();
    Delay( 10 );
}

void Lcd_t::Delay(uint32_t ms)
{
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq( &RCC_Clocks );

    volatile uint32_t count;
    count = RCC_Clocks.SYSCLK_Frequency * ms / 1000;

    while(count--);
}

void Lcd_t::PutPixel(uint8_t x, uint8_t y, Color_t color)
{

}

void Lcd_t::FillRect()
{

}

void Lcd_t::TextOut()
{

}
