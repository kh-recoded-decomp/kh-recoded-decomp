#include "nitro/types.h"

#define HW_VBLANK_COUNT_BUF 0x02fffc3c

typedef void (*PMCallback)(u32 result, void *arg);

typedef struct PMState {
    u16 initialized;
    u16 pad_02;
    u32 lastVBlankCount;
    u32 startVBlankCount;
    u8 pad_0c[0x20];
    u32 busy;
    PMCallback callback;
} PMState;

extern PMState data_020597c0;

extern void *PXI_Init_0200e1ec(void);
extern BOOL PXI_IsCallbackReady_0200e2e8(u32 fifoTag, int proc);
extern void PXI_SetFifoRecvCallback_0200e29c(u32 fifoTag, void *callback);
extern void WaitByLoop(s32 count);
extern void PMi_CommonCallback_02010298(u32 tag, u32 data, BOOL err);

static inline u32 OS_GetVBlankCount(void)
{
    return *(vu32 *)HW_VBLANK_COUNT_BUF;
}

void PM_Init_0201023c(void)
{
    if (data_020597c0.initialized) {
        return;
    }

    data_020597c0.initialized = TRUE;
    data_020597c0.busy = FALSE;
    data_020597c0.callback = NULL;

    PXI_Init_0200e1ec();

    while (!PXI_IsCallbackReady_0200e2e8(8, 1)) {
        WaitByLoop(100);
    }

    PXI_SetFifoRecvCallback_0200e29c(8, PMi_CommonCallback_02010298);

    data_020597c0.lastVBlankCount = data_020597c0.startVBlankCount = OS_GetVBlankCount();
}
