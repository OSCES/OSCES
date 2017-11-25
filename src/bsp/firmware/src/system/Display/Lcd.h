#ifndef LCD_H
#define LCD_H


#include "GpioDriver.h"
#include "VirtualPort.h"
#include "LcdTypes.h"

#define VOLTAGE_BUS     2, ## PE5, ## PE4
#define DATA_BUS        8, ## PG11, ## PG12, ## PG13, ## PG14, ## PG15, ## PA3, ## PB4, ## PB5

class Lcd_t
{
public:
    Lcd_t();
    ~Lcd_t();

public:
    void Init( void );
    void Clear( Color_t color );

    void PutPixel( uint8_t x, uint8_t y, Color_t color );
    void FillRect();
    void TextOut();

private:
    void SendCommand( LcdCommand_t command );
    void SendData( uint32_t data );

    void HwEnable( bool enable );
    void SwReset( void );

    void Delay(uint32_t ms);

private:
    VirtualPort_t* m_DataBus;       // D7..D0
    VirtualPort_t* m_VoltageBus;    // Vio, Vaux

    GpioPin_t*     m_RSpin;
    GpioPin_t*     m_RDpin;
    GpioPin_t*     m_WRpin;
    GpioPin_t*     m_DCpin;
};

#endif // LCD_H
