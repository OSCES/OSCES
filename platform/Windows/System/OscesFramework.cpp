#include "OscesFramework.h"

#include <SDL.h>
#include "SDL_thread.h"
#include "SDL_timer.h"
#include <stdio.h>

//extern OscesApplicationStatus_t osces_main( void );// OscesFrameworkInterface_t* system );
extern OscesApplicationStatus osces_main(OscesFrameworkInterface *system);

OscesFramework::OscesFramework()
{
    m_IsApplicationRun = true;
}

SysTimerInterface* OscesFramework::sysTimer()
{
    return m_pSysTimer;
}

DisplayInterface* OscesFramework::display()
{
    return m_pDisplay;
}

KeyboardInterface* OscesFramework::keyboard()
{
    return m_pKeyboard;
}

bool OscesFramework::applicationRunning()
{
    SDL_Event sdlEvent;

    while( SDL_PollEvent( &sdlEvent ) )
    {
        if( sdlEvent.type == SDL_WINDOWEVENT )
        {
            if( sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED )
            {
                m_pDisplay->WindowResize( sdlEvent.window.data1,sdlEvent.window.data2 );
            }
        }

        if( sdlEvent.type == SDL_KEYDOWN )
        {
            Key key;
            key.Event   = KeyPressed;
            key.KeyCode = (KeyCode)sdlEvent.key.keysym.scancode;

            m_pKeyboard->OnEvent( key );
        }
        else if( sdlEvent.type == SDL_KEYUP )
        {
            Key key;
            key.Event   = KeyReleased;
            key.KeyCode = (KeyCode)sdlEvent.key.keysym.scancode;

            m_pKeyboard->OnEvent( key );
        }

        if(  SDL_QUIT == sdlEvent.quit.type )
        {
            m_IsApplicationRun = false;
        }
    }

    return m_IsApplicationRun;
}

OscesFrameworkStatus OscesFramework::Init()
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

        m_pDisplay  = new DisplayPlatform;
        m_pKeyboard = new KeyboardPlatform;
        m_pSysTimer = new SysTimerPlatform;

    }while( false );

    m_pDisplay->init( 400, 300, true);

    m_pDisplay->clear();
    m_pDisplay->flip();
    m_pDisplay->clear();
    m_pDisplay->flip();

    return status;
}


void OscesFramework::DeInit()
{
    delete m_pSysTimer;
    delete m_pKeyboard;
    delete m_pDisplay;
}


#ifdef WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) //For Visual Studio
//int SDL_main(int argc, char *argv[])
#else
int main()
#endif
{
    OscesFramework *System = new OscesFramework;

    System->Init();

    osces_main(System);//pOscesFramework );

    System->DeInit();

    return 0;
}
