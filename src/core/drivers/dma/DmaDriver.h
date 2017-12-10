#ifndef DMA_DRIVER
#define DMA_DRIVER

#include <stdint.h>

typedef void (*DmaCompleateCallBack)(void *context);

extern void DmaInit();
extern void DmaM2MCopy(void *dst, void *src, uint32_t len, DmaCompleateCallBack fpDmaCompleateCallBack);
extern void DmaM2MFill(void *dst, uint8_t data, uint32_t len, DmaCompleateCallBack fpDmaCompleateCallBack);

#endif // DMA_DRIVER
