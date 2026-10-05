#include "nitro/types.h"

#define reg_GX_DISPCNT (*(vu32 *)0x04000000)
#define reg_G2_WIN0H (*(vu16 *)0x04000040)
#define reg_G2_WIN0V (*(vu16 *)0x04000044)
#define reg_G2_WININ (*(vu16 *)0x04000048)
#define reg_G2_WINOUT (*(vu16 *)0x0400004a)

typedef struct {
    u8 pad_000[0x480];
    u32 windowFading : 1;
    u32 pad_bits : 31;
    u8 pad_484[0x604 - 0x484];
    s32 fadeSize;
    volatile s32 phase;
} FieldScreen;

typedef struct {
    u32 pad_00;
    FieldScreen *screen;
} FieldManager;

extern FieldManager data_ov001_020a04a4;
extern void ConfigureFieldBgLayers_0206e818(void);

static inline void G2_SetWnd0InsidePlane(int wnd, BOOL effect)
{
    u32 tmp = (reg_G2_WININ & ~0x3f) | wnd;
    if (effect) {
        tmp |= 0x20;
    }
    reg_G2_WININ = (u16)tmp;
}

static inline void G2_SetWndOutsidePlane(int wnd, BOOL effect)
{
    u32 tmp = (reg_G2_WINOUT & ~0x3f) | wnd;
    if (effect) {
        tmp |= 0x20;
    }
    reg_G2_WINOUT = (u16)tmp;
}

static inline void G2_SetWnd0Position(int x1, int y1, int x2, int y2)
{
    reg_G2_WIN0H = (u16)(((x1 << 8) & 0xff00) | (x2 & 0xff));
    reg_G2_WIN0V = (u16)(((y1 << 8) & 0xff00) | (y2 & 0xff));
}

static inline void GX_SetVisibleWnd(int window)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0xe000) | (window << 13);
}

void UpdateFieldWindowFade_0206e8c4(void)
{
    FieldScreen *screen = data_ov001_020a04a4.screen;
    s32 size = screen->fadeSize;

    if (screen->phase > 0) {
        switch (screen->phase) {
        case 4:
            G2_SetWnd0InsidePlane(7, TRUE);
            G2_SetWndOutsidePlane(0xf, TRUE);
            G2_SetWnd0Position(0, 0x68, 0x68, 0xc0);
            GX_SetVisibleWnd(1);
            screen->phase++;
            break;
        case 9:
            GX_SetVisibleWnd(0);
            screen->phase = 0;
            break;
        }
    }
    if (screen->windowFading) {
        if (size >= 0) {
            G2_SetWnd0Position(0, 0x60 - size, 0xff, size + 0x60);
            return;
        }
        if (size == -2) {
            ConfigureFieldBgLayers_0206e818();
        }
        GX_SetVisibleWnd(0);
        screen->fadeSize = 0;
        screen->windowFading = 0;
    }
}
