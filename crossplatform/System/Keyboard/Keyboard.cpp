#include "Keyboard.h"

HandlersList_t Keyboard_t::HandlersList[] = { 0 };

Keyboard_t::Keyboard_t()
{

}

KeyboardStatus_t Keyboard_t::RegisterCallBack( void* pContext, KeyboardCallBack_t fp_CallBack )
{
    KeyboardStatus_t status = KEYBOARD_FAILED_STATUS;

    uint32_t size = sizeof( HandlersList ) / sizeof( HandlersList_t );

    for( uint32_t idx = 0; idx < size; idx ++ )
    {
        HandlersList_t* handler  = &HandlersList[ idx ];

        if( 0 == handler->CallBack )
        {
            handler->CallBack = fp_CallBack;
            handler->Context  = pContext;
            status = KEYBOARD_SUCCESS_STATUS;
            break;
        }
    }

    return status;
}


KeyboardStatus_t Keyboard_t::UnRegisterCallBack( KeyboardCallBack_t fp_CallBack )
{
    KeyboardStatus_t status = KEYBOARD_FAILED_STATUS;

    uint32_t size = sizeof( HandlersList ) / sizeof( HandlersList_t );

    for( uint32_t idx = 0; idx < size; idx ++ )
    {
        HandlersList_t* handler  = &HandlersList[ idx ];

        if( fp_CallBack == handler->CallBack )
        {
            handler->CallBack = 0;
            handler->Context  = 0;
            status = KEYBOARD_SUCCESS_STATUS;
            break;
        }
    }

    return status;
}

void Keyboard_t::ReceiveEvent( KeyboardEvent_t event, uint8_t scanCode )
{

    uint32_t size = sizeof( HandlersList ) / sizeof( HandlersList_t );

    for( uint32_t idx = 0; idx < size; idx ++ )
    {
        HandlersList_t* handler  = &HandlersList[ idx ];

        if( 0 != handler->CallBack )
        {
            handler->CallBack( handler->Context, event, scanCode );
            handler->Context  = 0;
        }
    }

}