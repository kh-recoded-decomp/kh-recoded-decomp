#include "nitro/types.h"

typedef void (*MIDmaCallback)(void *arg);

extern void MIi_CheckDma0SourceAddress_02005390(u32 dmaNo, u32 src, u32 size, u32 dir);
extern void WaitDmaChannel_02005218(u32 dmaNo);
extern void OSi_EnterDmaCallback_02001ea4(u32 dmaNo, MIDmaCallback function, void *arg);
extern void func_01ff85b4(u32 dmaNo, u32 src, u32 dest, u32 ctrl, u32 mode);

void MIi_DmaCopy32Async_0200511c(u32 dmaNo, const void *src, void *dest, u32 size, MIDmaCallback callback, void *arg, BOOL dmaEnable)
{
    MIi_CheckDma0SourceAddress_02005390(dmaNo, (u32)src, size, 0);

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
            func_01ff85b4(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0xc4000000, 0);
        } else {
            func_01ff85b4(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0x44000000, 4);
        }
    } else {
        if (dmaEnable) {
            func_01ff85b4(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0x84000000, 0);
        } else {
            func_01ff85b4(dmaNo, (u32)src, (u32)dest, (size >> 2) | 0x04000000, 4);
        }
    }
}
