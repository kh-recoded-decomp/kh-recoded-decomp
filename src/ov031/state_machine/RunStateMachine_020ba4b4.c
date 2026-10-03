#include "nitro/types.h"

typedef s32 (*StateHandler)(void);

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x10];
    s32 current;
    u8 pad_1c[0xa0];
    s32 frameCount;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern StateHandler data_ov031_020bc798[];
extern void ApplyOverlayScaleMode_020bab20(int mode);
extern void LeaveState_020bab00(void);

s32 RunStateMachine_020ba4b4(void)
{
    s32 next;

    g_activeState_020bc800->frameCount++;
    do {
        g_activeState_020bc800->flags &= 0x7fff;
        next = data_ov031_020bc798[g_activeState_020bc800->current]();
        if (next >= 0) {
            g_activeState_020bc800->current = next;
        }
    } while (g_activeState_020bc800->flags & 0x8000);
    if (g_activeState_020bc800->flags & 8) {
        ApplyOverlayScaleMode_020bab20(0);
    }
    if (g_activeState_020bc800->flags & 4) {
        LeaveState_020bab00();
    }
    return 0;
}
