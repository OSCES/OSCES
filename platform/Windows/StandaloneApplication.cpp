#include "OscesFrameworkInterface.h"

#include "GraphicalPrimitives/Line.h"




OscesApplicationStatus_t osces_main( OscesFrameworkInterface_t* pSystem )
{
  
	//pSystem->GetDisplay()->DrawPixel(  50, 50, 0xFF, 0xFF, 0xFF );
	

	Surface_t surface( SURFACE_ALLOCATE_IN_FRAME_BUFFER, pSystem->GetDisplay() );

	Line_t line( &surface );

	line.SetColor( Color_t( 100, 50, 100, 0, DISPLAY_PIXEL_FORMAT_DEFAULT ) );


	for( uint32_t idx = 0; idx < 300; idx++ )
	{
		line.SetColor( Color_t( 100, idx % 100, 100, 0, DISPLAY_PIXEL_FORMAT_DEFAULT ) );
		line.DrawHorizontal( 0, idx, 400 ); //x, y, size
	}

	line.SetColor( Color_t( 0xFF, 0xFF, 0xFF, 0, DISPLAY_PIXEL_FORMAT_DEFAULT ) );

	//line.DrawVertical( 50, 50, 50 );
	
	line.Draw( 100, 100, 200, 200 );
	line.Draw( 100, 100, 200, 0 );
	line.Draw( 200, 0, 200, 200 );

	//line.SetColor( Color_t( 0, 100, 100, 0, DISPLAY_PIXEL_FORMAT_DEFAULT ) );

	//line.DrawHorizontal( 10, 51, 200 ); //x, y, size
	//line.DrawHorizontal( 10, 52, 200 ); //x, y, size
	//line.DrawHorizontal( 0, 53, 395 ); //x, y, size
	//line.DrawHorizontal( 10, 54, 200 ); //x, y, size
	//line.DrawHorizontal( 10, 55, 200 ); //x, y, size


	//surface.CopyToRenderer( pSystem->GetDisplay(), 100, 100 );


	pSystem->GetDisplay()->Flip();


	while( pSystem->IsApplicationRun() )
    {
        //uint32_t usec = pSystem->GetSysTimer()->GetValueUsec();
        //asm("nop");
        //ThreadMCounter++;
        //pSystem->ThreadYield();
        //ThreadMCounter++;
        //asm("nop");
    }

	return OSCES_APP_SUCCESS_STATUS;
}