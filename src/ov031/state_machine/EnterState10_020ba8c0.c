#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void func_ov001_0206a72c(int mode);

u32 EnterState10_020ba8c0(void)
{
    OverlayState *state;

    state = g_activeState_020bc800;
    func_ov001_0206a72c((int)g_activeState_020bc800->mode);
    state->flags = state->flags | 0x20;
    return 10;
}
