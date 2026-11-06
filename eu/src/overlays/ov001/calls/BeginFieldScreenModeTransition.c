#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenState {
    u32 flags;
    s32 unk_04;
    fx32 x;
    fx32 y;
    u8 pad_10[0x54];
    u8 unk_64;
    u8 unk_65;
    u8 clearsSessionFlag : 1;
} ScreenState;

typedef struct Session {
    u8 pad_000[0x214];
    u32 flags;
} Session;

extern ScreenState *gFieldScreenTransitionWork;
extern Session *gFieldSessionWork;
extern u8 sOv001_RefreshWnd_0209eb2c[];
extern void SetScreenModeFlags(int enable, int mode);
extern void RestoreBrightnessOnce(void);
extern int GetMainBrightnessSetting(void);
extern int GetSubBrightnessSetting(void);
extern void DrawFlatRect(int nX0, int nY0, int nX1, int nY1, int nZ);
extern void InvokeForChannelOrBoth(u32 arg0, u32 arg1, int arg2, int channel);

void BeginFieldScreenModeTransition(int mode)
{
    ScreenState *screen = gFieldScreenTransitionWork;

    SetScreenModeFlags(1, mode);
    if (mode == 3) {
        return;
    }
    screen->x = GetMainBrightnessSetting() << 12;
    screen->y = GetSubBrightnessSetting() << 12;
    screen->unk_64 = 0;
    screen->unk_65 = 0;
    if (!(screen->flags & 0x40)) {
        screen->flags &= ~0x80;
        screen->unk_04 = 0x100;
        DrawFlatRect(0, 0, 0x100, 0xc0, 0);
        InvokeForChannelOrBoth(1, (u32)sOv001_RefreshWnd_0209eb2c, (int)RestoreBrightnessOnce, 0);
    }
    if (screen->clearsSessionFlag) {
        gFieldSessionWork->flags &= ~0x40000;
    }
}
