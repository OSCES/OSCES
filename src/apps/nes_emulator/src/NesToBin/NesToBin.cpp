// NesToBin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LOG printf

static int GetFileSize( FILE *file )
{
    int fileSizeBytes;

    fseek( file, 0, SEEK_END ); // set file pointer to end of file

    fileSizeBytes = ftell( file ); // get current pointer position in bytes (== file size in bytes)

    fseek( file, 0, SEEK_SET ); // return pointer to begin of file (it's very IMPORTANT)
    return fileSizeBytes;
}


int main( int argc, char *argv[] )
{
    printf( "Hello World %s\n", argv[ 1 ] );


    const char* pBinFile = argv[ 1 ];
    const char* pCppFile = argv[ 2 ];


    FILE* pFile = fopen( pBinFile, "rb" );

    int32_t fileSize = GetFileSize( pFile );


    uint8_t* pBuffer = new uint8_t[ fileSize ];
    uint8_t*  pOutBuffer = new uint8_t[ 16 * fileSize ];

    if( NULL != pBuffer )
    {
        memset( pBuffer, 0, fileSize );
        memset( pOutBuffer, 0, 16 * fileSize );

        fread( pBuffer, sizeof( uint8_t ), fileSize, pFile );

        fclose( pFile );

        char *pPrintBuffer = (char*)pOutBuffer;

        uint16_t len = 0;

        len = sprintf( pPrintBuffer, "#include <stdint.h> \r\nuint8_t file[] = \r\n{\r\n" );
        pPrintBuffer += len;

        for( uint32_t idx = 0; idx < fileSize; idx++ )
        {

            bool  isEnter = ( 0 != idx && 0 == ( idx % 16 ) ) ? true : false;

            if( true == isEnter )
            {

                len = sprintf( pPrintBuffer, "\r\n" );
                pPrintBuffer += len;
            }

            len = sprintf( pPrintBuffer, "0x%02x, ", pBuffer[ idx ] );
            pPrintBuffer += len;
        }

        len = sprintf( pPrintBuffer, "\r\n};\r\n" );
        pPrintBuffer += len;

        FILE* pFile = fopen( pCppFile, "wb" );

        if( NULL != pFile )
        {
            uint32_t fileLen = ( char* )pPrintBuffer - ( char* )pOutBuffer;

            fwrite( pOutBuffer, sizeof( uint8_t ), fileLen, pFile );
            fclose( pFile );
        }


        LOG( "%s\n", pOutBuffer );

        delete[] pBuffer;
        delete[] pOutBuffer;
    }




    printf( "%d\n", pFile );

    for( ;; )
    {

    }

}


