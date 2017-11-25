/**********************************************************************
 *
 * Filename:    MemTest.c
 *
 * Description: General-purpose memory testing functions.
 *
 * Notes:       This software can be easily ported to systems with
 *              different data bus widths by redefining 'datum'.
 *
 * Copyright (c) 1998 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/


#include "MemTest.h"


#define NULL (datum*)0x00


datum MemTestDataBus( datum *address )
{
    datum pattern;

    // Perform a walking 1's test at the given address.
    for( pattern = 1; pattern != 0; pattern <<= 1 )
    {
        // Write the test patter
        *address = pattern;

        //  Read it back (immediately is okay for this test).
        if( *address != pattern )
        {
            return pattern;
        }
    }

    return 0;
}

datum* MemTestAddressBus( volatile datum *startAddress, uint32_t bytesCount)
{
    uint32_t addressMask = ( bytesCount - 1 );
    uint32_t offset      = 0;
    uint32_t testOffset  = 0;

    datum pattern     = (datum)0xAAAAAAAA;
    datum antiPattern = (datum)0x55555555;

    //  Write the default pattern at each of the power-of-two offsets..
    for( offset = sizeof(uint32_t); (offset & addressMask) != 0; offset <<= 1 )
    {
        startAddress[offset] = pattern;
    }

    testOffset = 0;
    startAddress[ testOffset ] = antiPattern;

    // Check for address bits stuck high.
    for( offset = sizeof(uint32_t); (offset & addressMask) != 0; offset <<= 1)
    {
        if( startAddress[offset] != pattern )
        {
            return ( (datum*)&startAddress[offset] );
        }
    }

    startAddress[testOffset] = pattern;

    // Check for address bits stuck low or shorted.
    for (testOffset = sizeof(datum); (testOffset & addressMask) != 0; testOffset <<= 1)
    {
        startAddress[testOffset] = antiPattern;

        for (offset = sizeof(datum); (offset & addressMask) != 0; offset <<= 1)
        {
            if( (startAddress[offset] != pattern) && (offset != testOffset) )
            {
                return ( (datum*)&startAddress[testOffset] );
            }
        }

        startAddress[testOffset] = pattern;

    }

    return ( NULL );
}

datum* MemTestDevice(volatile datum *startAddress, uint32_t bytesCount)
{
    uint32_t offset;
    uint32_t wordsCount = bytesCount / sizeof(uint32_t);

    datum pattern;
    datum antipattern;

    // Fill memory with a known pattern.
    for( pattern = 1, offset = 0; offset < wordsCount; pattern++, offset++ )
    {
        startAddress[offset] = pattern;
    }

    // Check each location and invert it for the second pass.
    for( pattern = 1, offset = 0; offset < wordsCount; pattern++, offset++ )
    {
        if( startAddress[offset] != pattern )
        {
            return ( (datum*)&startAddress[offset] );
        }
        antipattern = ~pattern;
        startAddress[offset] = antipattern;
    }

    // Check each location for the inverted pattern and zero it.
    for( pattern = 1, offset = 0; offset < wordsCount; pattern++, offset++ )
    {
        antipattern = ~pattern;

        if( startAddress[offset] != antipattern )
        {
            return ( (datum*)&startAddress[offset] );
        }

        startAddress[offset] = 0;

    }

    return ( NULL );
}

