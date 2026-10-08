#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FrameWindow {
    u8 pad_00[4];
    s32 style;
    u8 pad_08[0x2c - 0x08];
    s32 bgLayer;
    u8 pad_30[0x38 - 0x30];
    u16 *screen;
    u8 pad_3c[0x78 - 0x3c];
    u16 width;
    u16 height;
} FrameWindow;

extern void *G2_GetBG2ScrPtr_02006e88(void);
extern void *G2_GetBG3ScrPtr_02006f80(void);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void CopyClippedScreenRegion_020167d0(void *dst, u16 *src, int srcX, int srcY, int dstX, int dstY, int width, int height, int tilesWide, int tilesHigh);

#define ROUND_TO_FX(v) ((fx32)((v) > 0 ? (float)((v) << 12) + 0.5f : (float)((v) << 12) - 0.5f))
static inline fx32 FX_Mul(fx32 v1, fx32 v2)
{
    return (fx32)(((s64)v1 * v2 + 0x800LL) >> 12);
}
#define DRAW(sx, sy, dx, dy, w, h) \
    do { \
        u16 *src = window->screen; \
        CopyClippedScreenRegion_020167d0(screen, src, sx, sy, dx, dy, (u32)src[0] >> 3, (u32)src[1] >> 3, w, h); \
    } while (0)

void DrawScaledWindowFrame_020c1d7c(FrameWindow *window, fx32 scale)
{
    int x;
    int j;
    int left;
    int bottom;
    int top;
    int tilesW;
    int tilesH;
    int i;
    void *screen;
    int baseW = window->width;
    int baseH = window->height;
    fx32 scaledW = FX_Mul(ROUND_TO_FX(baseW), scale);
    fx32 scaledH = FX_Mul(ROUND_TO_FX(baseH), scale);

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
    if (window->bgLayer == 2) {
        screen = G2_GetBG2ScrPtr_02006e88();
    } else {
        screen = G2_GetBG3ScrPtr_02006f80();
    }
    MIi_CpuClearFast_01ff8740(0, screen, 0x800);

    if (window->style == 0xf) {
        switch (tilesH) {
        case 1:
        case 2:
        case 3:
            DRAW(0, 8, left - 2, top - 1, 2, 2);
            DRAW(0x1e, 8, left + tilesW, top - 1, 2, 2);
            DRAW(0, 0xb, left - 2, top + tilesH - 1, 2, 2);
            DRAW(0x1e, 0xb, left + tilesW, top + tilesH - 1, 2, 2);
            break;
        default:
            DRAW(2, 8, left - 2, top - 1, 2, 3);
            DRAW(0x1c, 8, left + tilesW, top - 1, 2, 3);
            DRAW(2, 0xc, left - 2, top + tilesH - 2, 2, 3);
            DRAW(0x1c, 0xc, left + tilesW, top + tilesH - 2, 2, 3);
            break;
        }
    } else {
        DRAW(1, 0, left - 1, top - 1, 1, 1);
        DRAW(3, 0, left + tilesW, top - 1, 1, 1);
        DRAW(7, 0, left - 1, top + tilesH, 1, 1);
        DRAW(9, 0, left + tilesW, top + tilesH, 1, 1);
    }

    bottom = top + tilesH;
    for (i = 0; i < tilesW; i++) {
        DRAW(2, 0, left + i, top - 1, 1, 1);
        DRAW(8, 0, left + i, bottom, 1, 1);
    }

    if (window->style == 0xf) {
        switch (tilesH) {
        case 1:
        case 2:
        case 3:
            for (i = 1; i < tilesH - 1; i++) {
                DRAW(0, 0xa, left - 2, top + i, 2, 1);
                DRAW(0x1e, 0xa, left + tilesW, top + i, 2, 1);
            }
            break;
        default:
            for (i = 2; i < tilesH - 2; i++) {
                DRAW(2, 0xb, left - 2, top + i, 2, 1);
                DRAW(0x1c, 0xb, left + tilesW, top + i, 2, 1);
            }
            break;
        }
    } else {
        for (i = 0; i < tilesH; i++) {
            DRAW(4, 0, left - 1, top + i, 2, 1);
            DRAW(6, 0, left + tilesW, top + i, 1, 1);
        }
    }

    for (j = 0; j < tilesH; j++) {
        x = left;
        for (i = 0; i < tilesW; i++) {
            DRAW(5, 0, x, top, 1, 1);
            x++;
        }
        top++;
    }
}
