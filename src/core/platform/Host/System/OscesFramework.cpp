#include "OscesFramework.h"

#include <SDL.h>
#include "SDL_thread.h"
#include "SDL_timer.h"
#include <stdio.h>

//extern OscesApplicationStatus_t osces_main( void );// OscesFrameworkInterface_t* system );
extern OscesApplicationStatus osces_main(OscesFrameworkInterface *system);

OscesCore::OscesCore()
{
    m_applicationRunning = true;
}

SysTimerInterface* OscesCore::sysTimer()
{
    return m_sysTimer;
}

DisplayInterface* OscesCore::display()
{
    return m_display;
}

KeyboardInterface* OscesCore::keyboard()
{
    return m_keyboard;
}

bool OscesCore::applicationRunning()
{
    SDL_Event sdlEvent;

    while( SDL_PollEvent( &sdlEvent ) )
    {
        if( sdlEvent.type == SDL_WINDOWEVENT )
        {
            if( sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED )
            {
                m_display->WindowResize( sdlEvent.window.data1,sdlEvent.window.data2 );
            }
        }

        if( sdlEvent.type == SDL_KEYDOWN )
        {
            Key key;
            key.Event   = KeyPressed;
            key.KeyCode = (KeyCode)sdlEvent.key.keysym.scancode;

            m_keyboard->OnEvent( key );
        }
        else if( sdlEvent.type == SDL_KEYUP )
        {
            Key key;
            key.Event   = KeyReleased;
            key.KeyCode = (KeyCode)sdlEvent.key.keysym.scancode;

            m_keyboard->OnEvent( key );
        }

        if(  SDL_QUIT == sdlEvent.quit.type )
        {
            m_applicationRunning = false;
        }
    }

    return m_applicationRunning;
}

OscesFrameworkStatus OscesCore::init()
{
    OscesFrameworkStatus status = OSCES_FRAMEWORK_INIT_SUCCESS;

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

        m_display  = new DisplayPlatform;
        m_keyboard = new KeyboardPlatform;
        m_sysTimer = new SysTimerPlatform;

    }while( false );

    m_display->init( 400, 300, true);

    m_display->clear();
    m_display->flip();
    m_display->clear();
    m_display->flip();

    return status;
}


void OscesCore::deInit()
{
    delete m_sysTimer;
    delete m_keyboard;
    delete m_display;
}

#define NEEDS_OSCES_MAIN
#if defined(NEEDS_OSCES_MAIN)
int osces_main(int, char **);
#define main osces_main
#endif

int main(int argc, char *argv[])
{
    OscesCore *system = new OscesCore;
    system->init();
    main(system);
    system->deInit();

    return 0;
}
