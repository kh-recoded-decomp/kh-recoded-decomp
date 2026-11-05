#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenState {
    u32 flags;
    s32 unk_04;
    fx32 mainBrightness;
    fx32 subBrightness;
    u8 pad_10[8];
    s32 unk_18;
} ScreenState;

typedef struct Session {
    u8 pad_000[0x214];
    u32 flags;
} Session;

extern ScreenState *data_ov001_020a04a0;
extern Session *data_ov001_020a0480;
extern void SetScreenModeFlags(int enable, int mode);
extern int GetMainBrightnessSetting(void);
extern int GetSubBrightnessSetting(void);

void BeginScreenFadeOut(int mode)
{
    ScreenState *screen = data_ov001_020a04a0;

    data_ov001_020a0480->flags |= 0x40000;
    SetScreenModeFlags(0, mode);
    if (mode == 3) {
        return;
    }
    screen->mainBrightness = GetMainBrightnessSetting() << 12;
    screen->subBrightness = GetSubBrightnessSetting() << 12;
    if (!(screen->flags & 0x40)) {
        screen->unk_18 = 0x1000;
        screen->unk_04 = 0x6000;
    }
}
