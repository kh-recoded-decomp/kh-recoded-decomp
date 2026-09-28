#include "nitro/types.h"

typedef void (*PxiOsRecvCallback)(int unused, int status);

extern void *PXI_Init_0200e1ec(void);
extern BOOL PXI_IsCallbackReady_0200e2e8(u32 tag, BOOL bSend);
extern void PXI_SetFifoRecvCallback_0200e29c(u32 tag, PxiOsRecvCallback callback);
extern void func_0200202c(int unused, int status);

extern u16 g_pxiOsChannelReady_02056ec4;

void InitOsPxiChannel_02004a0c(void)
{
    if (g_pxiOsChannelReady_02056ec4 != 0) {
        return;
    }
    g_pxiOsChannelReady_02056ec4 = 1;

    PXI_Init_0200e1ec();
    while (!PXI_IsCallbackReady_0200e2e8(0xc, TRUE)) {
    }
    PXI_SetFifoRecvCallback_0200e29c(0xc, func_0200202c);
}
