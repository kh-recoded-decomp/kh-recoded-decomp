#include "nitro/types.h"

typedef struct ScreenState {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x14];
    s8 subMode;
} ScreenState;

typedef struct SessionState {
    u8 pad_00[0x214];
    u32 flags;
} SessionState;

extern ScreenState *data_ov035_020bc500;
extern SessionState *data_ov001_020a0480;
extern BOOL IsScreenModeIdle(void);
extern void Panel_CaptureBrightness(void);

int FinishAreaScreenTransition(void)
{
    ScreenState *screen = data_ov035_020bc500;

    if (!IsScreenModeIdle()) {
        return -1;
    }
    if (!(screen->flags & 0x4000)) {
        if (screen->subMode != 3) {
            data_ov001_020a0480->flags &= ~0x40000;
            Panel_CaptureBrightness();
        }
        screen->subMode = -1;
    }
    screen->flags &= ~0x20;
    return 5;
}
