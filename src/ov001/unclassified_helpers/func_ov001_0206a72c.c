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

extern ScreenState *data_ov001_020a0480;
extern Session *data_ov001_020a0460;
extern u8 data_ov001_0209eb0c[];
extern void func_ov001_0206a670(int enable, int mode);
extern void func_ov001_0206a630(void);
extern int func_02029f48(void);
extern int func_02029f58(void);
extern void DrawFlatRect_0206a424(int nX0, int nY0, int nX1, int nY1, int nZ);
extern void InvokeForChannelOrBoth_0200110c(u32 arg0, u32 arg1, int arg2, int channel);

void func_ov001_0206a72c(int mode)
{
    ScreenState *screen = data_ov001_020a0480;

    func_ov001_0206a670(1, mode);
    if (mode == 3) {
        return;
    }
    screen->x = func_02029f48() << 12;
    screen->y = func_02029f58() << 12;
    screen->unk_64 = 0;
    screen->unk_65 = 0;
    if (!(screen->flags & 0x40)) {
        screen->flags &= ~0x80;
        screen->unk_04 = 0x100;
        DrawFlatRect_0206a424(0, 0, 0x100, 0xc0, 0);
        InvokeForChannelOrBoth_0200110c(1, (u32)data_ov001_0209eb0c, (int)func_ov001_0206a630, 0);
    }
    if (screen->clearsSessionFlag) {
        data_ov001_020a0460->flags &= ~0x40000;
    }
}
