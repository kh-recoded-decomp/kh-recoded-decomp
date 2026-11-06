#include "nitro/types.h"

typedef struct VBlankCallbackNode {
    u32 pad_00[5];
    void (*callback)(void);
    struct VBlankCallbackNode *next;
} VBlankCallbackNode;

typedef struct VBlankCallbackState {
    u32 counter;
    s32 activeList;
    u32 pad_08;
    VBlankCallbackNode *lists[1];
} VBlankCallbackState;

extern void GXx_SetMasterBrightness_(u16 *dst, int value);

extern u8 gPendingMasterBrightnessMask;
extern s8 gCachedMasterBrightnessStorage[];
extern VBlankCallbackState gVBlankCallbackState;
extern u32 gVBlankCallbackExecutionFlags;
extern char SDK_AUTOLOAD_DTCM_START[];

void OSi_VBlankInterruptHandler(void)
{
    VBlankCallbackState *state;
    VBlankCallbackNode *node;
    u8 flags;

    state = &gVBlankCallbackState;
    flags = gPendingMasterBrightnessMask;
    state->counter++;
    if (flags & 1) {
        GXx_SetMasterBrightness_((u16 *)0x0400006c, gCachedMasterBrightnessStorage[0]);
    }
    if (flags & 2) {
        GXx_SetMasterBrightness_((u16 *)0x0400106c, gCachedMasterBrightnessStorage[1]);
    }
    gPendingMasterBrightnessMask = 0;
    gVBlankCallbackExecutionFlags |= 1;
    node = state->lists[state->activeList];
    while (node != NULL) {
        node->callback();
        node = node->next;
    }
    gVBlankCallbackExecutionFlags &= ~1;
    {
        u32 base = (u32)SDK_AUTOLOAD_DTCM_START + 0x3000;
        *(u32 *)(base + 0xff8) |= 1;
    }
}
