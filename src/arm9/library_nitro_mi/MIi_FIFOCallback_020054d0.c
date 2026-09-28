#include "nitro/types.h"

typedef void (*MIDmaCallback)(void *arg);

typedef struct {
    volatile u32 isBusy;
    u32 dmaNo;
    u32 src;
    u32 length;
    MIDmaCallback callback;
    void *arg;
} GXDmaParams;

extern GXDmaParams data_02056ee8;
extern void geometry_fifo_dma_complete_02005584(void *arg);
extern void OSi_EnterDmaCallback_02001ea4(u32 dmaNo, MIDmaCallback function, void *arg);
extern void func_01ff85b4(u32 dmaNo, u32 src, u32 dest, u32 ctrl, u32 mode);
extern u32 OS_ResetRequestIrqMask(u32 mask);

void MIi_FIFOCallback_020054d0(void)
{
    u32 length;
    u32 src;

    if (data_02056ee8.length == 0) {
        return;
    }

    length = (data_02056ee8.length >= 0x1d8) ? 0x1d8 : data_02056ee8.length;
    src = data_02056ee8.src;

    data_02056ee8.length -= length;
    data_02056ee8.src += length;

    if (data_02056ee8.length == 0) {
        OSi_EnterDmaCallback_02001ea4(data_02056ee8.dmaNo, geometry_fifo_dma_complete_02005584, 0);
        func_01ff85b4(data_02056ee8.dmaNo, src, 0x4000400, (length >> 2) | 0xc4400000, 0);
        OS_ResetRequestIrqMask(0x200000);
    } else {
        func_01ff85b4(data_02056ee8.dmaNo, src, 0x4000400, (length >> 2) | 0x84400000, 0);
        OS_ResetRequestIrqMask(0x200000);
    }
}
