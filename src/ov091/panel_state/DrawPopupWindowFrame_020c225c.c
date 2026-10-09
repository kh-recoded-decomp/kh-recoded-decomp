#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef float f32;

typedef struct PopupWindow {
    u8 pad_00[0x54];
    u16 width;
    u16 height;
} PopupWindow;

typedef struct PopupManager {
    u8 pad_00[0x20];
    u16 *frameScreen;
} PopupManager;

extern PopupManager *g_popupManager_020c373c;
extern void *G2S_GetBG2ScrPtr_02006f0c(void);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void CopyClippedScreenRegion_020167d0(void *dst, u16 *src, int srcX, int srcY, int dstX, int dstY, int width, int height, int tilesWide, int tilesHigh);

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? (0.5f + 4096.0f * (f32)(n)) : (4096.0f * (f32)(n) - 0.5f)))
#define DRAW(sx, dx, dy) \
    do { \
        u16 *src = g_popupManager_020c373c->frameScreen; \
        CopyClippedScreenRegion_020167d0(screen, src, sx, 0, dx, dy, (u32)src[0] >> 3, (u32)src[1] >> 3, 1, 1); \
    } while (0)

static inline fx32 FX_Mul(fx32 v1, fx32 v2)
{
    return (fx32)(((s64)v1 * v2 + 0x800LL) >> 12);
}

void DrawPopupWindowFrame_020c225c(PopupWindow *window, fx32 scale)
{
    void *screen = G2S_GetBG2ScrPtr_02006f0c();
    int x;
    int j;
    int left;
    int bottom;
    int top;
    int right;
    int tilesW;
    int tilesH;
    int i;
    int baseW = window->width;
    int baseH = window->height;
    fx32 scaledW = FX_Mul(INT_TO_FX32(baseW), scale);
    fx32 scaledH = FX_Mul(INT_TO_FX32(baseH), scale);

    tilesW = scaledW >> 12;
    tilesH = scaledH >> 12;
    if (tilesW < 2) {
        tilesW = 2;
    } else if (scaledW & 0xfff) {
        tilesW++;
    }
    if (tilesH < 1) {
        tilesH = 1;
    } else if (scaledH & 0xfff) {
        tilesH++;
    }
    left = 16 - tilesW / 2;
    top = 12 - tilesH / 2;
    MIi_CpuClearFast_01ff8740(0, screen, 0x800);

    DRAW(1, left - 1, top - 1);

    DRAW(3, right = left + tilesW, top - 1);
    DRAW(7, left - 1, top + tilesH);
    DRAW(9, right, top + tilesH);

    bottom = top + tilesH;
    for (i = 0; i < tilesW; i++) {
        DRAW(2, left + i, top - 1);
        DRAW(8, left + i, bottom);
    }
    for (i = 0; i < tilesH; i++) {
        DRAW(4, left - 1, top + i);
        DRAW(6, right, top + i);
    }
    for (j = 0; j < tilesH; j++) {
        x = left;
        for (i = 0; i < tilesW; i++) {
            DRAW(5, x, top);
            x++;
        }
        top++;
    }
}
