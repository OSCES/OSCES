
#include "main.h"
#include "Snake.h"
#include "OscesFrameworkInterface.h"
#include "KeyCode.h"



void KeyboardCallBack( void* pContext, Key_t key )
{
    Snake_t* pSnake = static_cast< Snake_t* >( pContext );

    SnakeDirection_t direction = NONE;

    switch( key.KeyCode )
    {
        case KEY_UP   : direction = UP;    break;
        case KEY_DOWN : direction = DOWN;  break;
        case KEY_RIGHT: direction = RIGHT; break;
        case KEY_LEFT : direction = LEFT;  break;

        default:
        break;
    };

    pSnake->SetDirection( direction ); 
}

OscesApplicationStatus_t osces_main( OscesFrameworkInterface_t* system )
{

    Snake_t* pSnake = new Snake_t( 10, 10 );

    system->GetKeyboard()->RegisterCallBack( pSnake, KeyboardCallBack );



    pSnake->Init( system->GetDisplay() );

    pSnake->SetDirection( RIGHT ); 


    uint32_t lastTickValue = 0;

    do
    {

        uint32_t tickValue = system->GetSysTimer()->GetValueUsec();

        uint32_t deltaTickValue = tickValue - lastTickValue;
 
        if( deltaTickValue >= 1000000 )
        {
            lastTickValue = tickValue;
            system->GetDisplay()->Clear();
            pSnake->Run();
            system->GetDisplay()->Flip();
        }
    } while( system->IsApplicationRun() );

    delete pSnake;

    return OSCES_APP_SUCCESS_STATUS;
}