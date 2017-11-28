/* 
 * File:   main.cpp
 * Author: IBilorus
 *
 * Created on 17 Сентябрь 2013 г., 15:12
 */

#include "SDL.h"
#include "Display/Display.h"
#include "Cpu/Cpu.h"
#include "Orion.h"


Display_t m_Display;
Orion_t   m_Orion;

void PresentFrameCallBack( void* pContext, uint8_t* pData, uint16_t lineNumber )
{
   
    if( 0 != pData )
    {
        for( uint16_t idx = 0; idx != 384; idx ++ )
        {
			//m_Display.GetFrameBuffer();
            m_Display.DrawPixel( idx, lineNumber, pData[ 0 ], pData[ 1  ], pData[ 2 ] );
            pData += 3;
        }
    }
    else
    {
        m_Display.Flip();
    }
}


#ifdef __WIN32__
#include <windows.h>
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw )
#else
int main()
#endif
{
    m_Display.Init( 384, 256, false );

    m_Orion.SetPresentLineCallBack( 0, PresentFrameCallBack );
    m_Orion.Reset();
    
	bool IsApplicationRun = true;

    for( ; IsApplicationRun ; )
    {

		SDL_Event sdlEvent;

		while( SDL_PollEvent( &sdlEvent ) )
		{
			if( sdlEvent.type == SDL_WINDOWEVENT )
			{
				if( sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED )
				{
					m_Display.WindowResize( sdlEvent.window.data1,sdlEvent.window.data2 );
				}
			}
      
			if( SDL_KEYDOWN == sdlEvent.type )
			{
				uint8_t key = sdlEvent.key.keysym.sym;
			
                                //uint8_t code = sdlEvent.key.keysym.scancode;
                                
				if( ( key >= SDLK_a ) && ( key <= SDLK_z ) )
				{
					key -= 32;
				}
				m_Orion.PressKey( key );

			}

			if( SDL_KEYUP == sdlEvent.type )
			{
				uint8_t key = sdlEvent.key.keysym.sym;

				if( ( key >= SDLK_a ) && ( key <= SDLK_z ) )
				{
					key -= 32;
				}
				m_Orion.UnPressKey( key );
			}
        
			if(  SDL_QUIT == sdlEvent.quit.type )
			{
				IsApplicationRun = false;
				break;
			}

			if( sdlEvent.type == SDL_KEYDOWN )
			{
				if( sdlEvent.key.keysym.sym == SDLK_ESCAPE )
				{ 
					IsApplicationRun = false;
					break; 
				} 
			}

		}

		m_Orion.RunFrame();
                SDL_Delay( 0 );
	}

	atexit(SDL_Quit); 
 
 return 0;  
}

