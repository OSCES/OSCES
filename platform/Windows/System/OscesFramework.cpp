#include "include/OscesFramework.h"


#ifdef WIN32
#include "Display/Display.h"
#include "Keyboard/KeyboardPlatform.h"
#endif


#include "SDL_thread.h"
#include "SDL_timer.h"
#include <stdio.h>


Display_t  Display;
KeyboardPlatform_t Keyboard;
OscesFramework_t OscesFramework;
bool IsApplicationRunEnable = true;

DisplayInterface_t* OscesFramework_t::GetDisplay()
{
    DisplayInterface_t* pDisplayInterface = &Display;
    return  pDisplayInterface;
}

KeyboardInterface_t* OscesFramework_t::GetKeyboard()
{
    return &Keyboard;
}


#ifdef WIN32
#include <windows.h>
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow ) //For VS2012
#else
int main()
#endif
{
    OscesFrameworkInit();

    osces_main( &OscesFramework );

    OscesFrameworkDeInit();

    return 0;
}


bool OscesFramework_t::IsApplicationRun()
{
    SDL_Event sdlEvent;

    while( SDL_PollEvent( &sdlEvent ) )
    {
        if( sdlEvent.type == SDL_WINDOWEVENT )
        {
            if( sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED )
            {
                Display.WindowResize( sdlEvent.window.data1,sdlEvent.window.data2 );
            }
        }
            

        if( sdlEvent.type == SDL_KEYDOWN )
        {
            Keyboard.ReceiveEvent( KEYBOARD_PRESSED, sdlEvent.key.keysym.sym );
        }
        else if( sdlEvent.type == SDL_KEYUP )
        {
            Keyboard.ReceiveEvent( KEYBOARD_UNPRESSED, sdlEvent.key.keysym.sym );
        }

            

        if(  SDL_QUIT == sdlEvent.quit.type )
        {
            IsApplicationRunEnable = false;
        }
            
    }

    return IsApplicationRunEnable;
}

OscesFrameworkStatus_t OscesFrameworkInit()
{
    OscesFrameworkStatus_t status = OSCES_FRAMEWORK_INIT_SUCCESS;

    do
    {
        if( 0 != SDL_Init( SDL_INIT_TIMER ) )
        {
            status = OSCES_FRAMEWORK_INIT_FAILED;
            break;
        }

        if( 0 != SDL_Init( SDL_INIT_VIDEO ) )
        {
            status = OSCES_FRAMEWORK_INIT_FAILED;
            break;
        }

    }while( false );

    Display.Init( 400, 300);

    Display.Clear();
    Display.Flip();
    Display.Clear();
    Display.Flip();

    return status;
}


void OscesFrameworkDeInit()
{

}