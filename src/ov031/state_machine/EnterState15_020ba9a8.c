#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void func_ov001_02066810(void);
extern void func_ov001_02087628(u32 a);

u32 EnterState15_020ba9a8(void)
{
    OverlayState *state;

    state = g_activeState_020bc800;
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x20;
    if ((state->flags & 0x10) == 0) {
        func_ov001_02066810();
        func_ov001_02087628(1);
    }
    return 0xf;
}
