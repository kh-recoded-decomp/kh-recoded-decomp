#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x14];
    s8 subMode;
} ScreenState;

typedef struct {
    u8 pad_00[0x214];
    u32 flags;
} SessionState;

extern ScreenState *data_ov035_020bc4e0;
extern SessionState *data_ov001_020a0460;
extern BOOL func_ov001_0206a814(void);
extern void Panel_CaptureBrightness_0207b704(void);

int func_ov040_020bd548(void) {
    ScreenState *screen = data_ov035_020bc4e0;
    if (!func_ov001_0206a814()) {
        return -1;
    }
    if (!(screen->flags & 0x4000)) {
        if (screen->subMode != 3) {
            data_ov001_020a0460->flags &= ~0x40000;
            Panel_CaptureBrightness_0207b704();
        }
        screen->subMode = -1;
    }
    screen->flags &= ~0x20;
    return 5;
}
