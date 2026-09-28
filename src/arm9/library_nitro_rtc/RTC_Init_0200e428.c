#include "nitro/types.h"

typedef struct RtcWork {
    u16 initialized;
    u8 pad_02[2];
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u8 pad_14[0xc];
    u32 unk_20;
} RtcWork;

extern RtcWork data_02057c0c;
extern void PXI_Init_0200e1ec(void);
extern BOOL PXI_IsCallbackReady_0200e2e8(u32 fifoTag, int kind);
extern void PXI_SetFifoRecvCallback_0200e29c(u32 fifoTag, void *callback);
extern void func_0200e5b8(int fifoTag, u32 data);

void RTC_Init_0200e428(void)
{
    if (data_02057c0c.initialized != 0)
        return;

    data_02057c0c.initialized = 1;
    data_02057c0c.unk_04 = 0;
    data_02057c0c.unk_08 = 0;
    data_02057c0c.unk_20 = 0;
    data_02057c0c.unk_0C = 0;
    data_02057c0c.unk_10 = 0;

    PXI_Init_0200e1ec();
    while (!PXI_IsCallbackReady_0200e2e8(5, 1)) {
    }
    PXI_SetFifoRecvCallback_0200e29c(5, (void *)&func_0200e5b8);
}
