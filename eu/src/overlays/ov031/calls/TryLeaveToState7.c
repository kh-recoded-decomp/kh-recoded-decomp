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

extern OverlayState *gOv031SceneWorkStorage;
extern PanelState *gFieldSessionWork;
extern BOOL IsScreenModeIdle(void);
extern void Panel_CaptureBrightness(void);

u32 TryLeaveToState7(void)
{
    OverlayState *state = gOv031SceneWorkStorage;

    if (!IsScreenModeIdle()) {
        return 0xffffffff;
    }
    if (!(state->flags & 0x4000)) {
        if (state->mode != 3) {
            gFieldSessionWork->displayFlags &= ~0x40000;
            Panel_CaptureBrightness();
        }
        state->mode = -1;
    }
    state->flags &= ~0x20;
    return 7;
}
