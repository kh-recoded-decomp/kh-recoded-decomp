#include "nitro/types.h"

typedef void (*MIDmaCallback)(void *arg);

extern void WaitDmaChannel_02005218(u32 dmaNo);
extern void OSi_EnterDmaCallback_02001ea4(u32 dmaNo, MIDmaCallback function, void *arg);
extern void func_01ff85b4(u32 dmaNo, u32 src, u32 dest, u32 ctrl, u32 mode);

void MIi_DmaFill32Async_02005014(u32 dmaNo, void *dest, u32 data, u32 size, MIDmaCallback callback, void *arg, BOOL dmaEnable)
{
    if (size == 0) {
        if (callback) {
            callback(arg);
        }
        return;
    }

    WaitDmaChannel_02005218(dmaNo);

    if (callback) {
        OSi_EnterDmaCallback_02001ea4(dmaNo, callback, arg);
        if (dmaEnable) {
            func_01ff85b4(dmaNo, data, (u32)dest, (size >> 2) | 0xc5000000, 0x10);
        } else {
            func_01ff85b4(dmaNo, data, (u32)dest, (size >> 2) | 0x45000000, 0x14);
        }
    } else {
        if (dmaEnable) {
            func_01ff85b4(dmaNo, data, (u32)dest, (size >> 2) | 0x85000000, 0x10);
        } else {
            func_01ff85b4(dmaNo, data, (u32)dest, (size >> 2) | 0x05000000, 0x14);
        }
    }
}
