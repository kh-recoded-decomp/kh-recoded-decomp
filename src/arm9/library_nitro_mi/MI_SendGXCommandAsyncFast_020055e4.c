#include "nitro/types.h"

typedef void (*MIDmaCallback)(void *arg);

typedef struct {
    volatile u32 isBusy;
    u32 dmaNo;
    u8 pad_08[8];
    MIDmaCallback callback;
    void *arg;
} GXDmaParams;

extern GXDmaParams data_02056ee8;
extern void MIi_DMAFastCallback_020056a0(void *arg);
extern void MIi_CheckAnotherAutoDMA_02005304(int dmaNo, u32 timing);
extern void MIi_CheckDma0SourceAddress_02005390(u32 dmaNo, u32 src, u32 size, u32 dir);
extern void WaitDmaChannel_02005218(int channel);
extern void OSi_EnterDmaCallback_02001ea4(u32 dmaNo, MIDmaCallback function, void *arg);
extern void func_01ff85b4(u32 dmaNo, u32 src, u32 dest, u32 ctrl, u32 arg5);

void MI_SendGXCommandAsyncFast_020055e4(u32 dmaNo, u32 src, u32 commandLength, MIDmaCallback callback, void *arg)
{
    if (commandLength == 0) {
        if (callback != 0) {
            callback(arg);
        }
        return;
    }

    while (data_02056ee8.isBusy != 0) {
    }

    data_02056ee8.isBusy = 1;
    data_02056ee8.dmaNo = dmaNo;
    data_02056ee8.callback = callback;
    data_02056ee8.arg = arg;

    MIi_CheckAnotherAutoDMA_02005304(dmaNo, 0x38000000);
    MIi_CheckDma0SourceAddress_02005390(dmaNo, src, commandLength, 0);
    WaitDmaChannel_02005218(dmaNo);

    OSi_EnterDmaCallback_02001ea4(dmaNo, MIi_DMAFastCallback_020056a0, 0);
    func_01ff85b4(dmaNo, src, 0x4000400, (commandLength >> 2) | 0xfc400000, 0);
}
