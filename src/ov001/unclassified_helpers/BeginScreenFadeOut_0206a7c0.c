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

extern ScreenState *data_ov001_020a0480;
extern Session *data_ov001_020a0460;
extern void SetScreenFadeMode_0206a670(int enable, int mode);
extern int GetMainBrightness_02029f48(void);
extern int GetSubBrightness_02029f58(void);

void BeginScreenFadeOut_0206a7c0(int mode)
{
    ScreenState *screen = data_ov001_020a0480;

    data_ov001_020a0460->flags |= 0x40000;
    SetScreenFadeMode_0206a670(0, mode);
    if (mode == 3) {
        return;
    }
    screen->mainBrightness = GetMainBrightness_02029f48() << 12;
    screen->subBrightness = GetSubBrightness_02029f58() << 12;
    if (!(screen->flags & 0x40)) {
        screen->unk_18 = 0x1000;
        screen->unk_04 = 0x6000;
    }
}
