#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 handle;
} PxiChannelState;

extern PxiChannelState *g_pxiChannelState_020ca1e4;
extern void *PXI_Init_020c2864();
extern void *PXI_Init_02028950();

void DestroyPxiChannelState_020c2dbc(void)
{
    PXI_Init_020c2864(g_pxiChannelState_020ca1e4->handle);
    PXI_Init_02028950();
    g_pxiChannelState_020ca1e4->handle = 0xffffffff;
    g_pxiChannelState_020ca1e4 = (PxiChannelState *)0;
}
