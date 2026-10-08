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

extern u8 data_02060388;
extern s8 data_02060389[];
extern VBlankCallbackState gVBlankCallbackState;
extern u32 data_020569c8;
extern char SDK_AUTOLOAD_DTCM_START[];

void OSi_VBlankInterruptHandler(void)
{
    VBlankCallbackState *state;
    VBlankCallbackNode *node;
    u8 flags;

    state = &gVBlankCallbackState;
    flags = data_02060388;
    state->counter++;
    if (flags & 1) {
        GXx_SetMasterBrightness_((u16 *)0x0400006c, data_02060389[0]);
    }
    if (flags & 2) {
        GXx_SetMasterBrightness_((u16 *)0x0400106c, data_02060389[1]);
    }
    data_02060388 = 0;
    data_020569c8 |= 1;
    node = state->lists[state->activeList];
    while (node != NULL) {
        node->callback();
        node = node->next;
    }
    data_020569c8 &= ~1;
    {
        u32 base = (u32)SDK_AUTOLOAD_DTCM_START + 0x3000;
        *(u32 *)(base + 0xff8) |= 1;
    }
}
