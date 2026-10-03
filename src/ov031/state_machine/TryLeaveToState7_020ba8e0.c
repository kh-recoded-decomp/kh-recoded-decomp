#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

typedef struct {
    u8 pad_00[0x214];
    u32 displayFlags;
} PanelState;

extern OverlayState *g_activeState_020bc800;
extern PanelState *data_ov001_020a0460;
extern BOOL IsScreenModeIdle_0206a814(void);
extern void Panel_CaptureBrightness_0207b704(void);

u32 TryLeaveToState7_020ba8e0(void)
{
    OverlayState *state = g_activeState_020bc800;

    if (!IsScreenModeIdle_0206a814()) {
        return 0xffffffff;
    }
    if (!(state->flags & 0x4000)) {
        if (state->mode != 3) {
            data_ov001_020a0460->displayFlags &= ~0x40000;
            Panel_CaptureBrightness_0207b704();
        }
        state->mode = -1;
    }
    state->flags &= ~0x20;
    return 7;
}
