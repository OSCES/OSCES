#ifndef _DMA_DRIVER_
#define _DMA_DRIVER_

#include <stdint.h>

typedef void ( *DmaCompleateCallBack )( void* pContext );


extern void DmaInit();
extern void DmaM2MCopy( void* pDestination, void* pSource, uint32_t len, DmaCompleateCallBack fpDmaCompleateCallBack );
extern void DmaM2MFill( void* pDestination, uint8_t data , uint32_t len, DmaCompleateCallBack fpDmaCompleateCallBack );

#endif // _DMA_DRIVER_
