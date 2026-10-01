#include "nitro/types.h"

typedef struct ScreenImage {
    u32 pad_00[4];
    u32 size;
    void *data;
} ScreenImage;

typedef struct ScreenInfo {
    u8 pad_00[8];
    u16 width;
    u16 height;
} ScreenInfo;

typedef struct ScaledMenu {
    u8 pad_00[0x14];
    u16 *screenData;
    ScreenImage *image;
    u8 pad_1c[4];
    s32 scale;
    BOOL loaded;
    BOOL needsLoad;
    BOOL needsRefresh;
    u8 pad_30[0x48 - 0x30];
    s32 centerX;
    s32 centerY;
    u8 pad_50[8];
    u8 spriteManager[1];
} ScaledMenu;

extern ScaledMenu *data_ov023_020b6f64;
extern ScreenInfo *func_ov001_0207123c(void);
extern void *func_ov027_020b9df0(ScreenInfo *screen, int id);
extern s32 func_02023dbc(s32 numerator, s32 denominator);
extern void func_02007be0(void *data, int offset, u32 size);
extern void CopyClippedScreenRegion_020167d0(void *dst, u16 *src, int srcX, int srcY, int dstX, int dstY, int width, int height, int tilesWide, int tilesHigh);
extern void func_02007860(void *tileMap, int offset, int size);
extern void func_020067b0(void *reg, s32 *matrix, int x, int y, s32 centerX, s32 centerY);
extern void func_0204f12c(void *manager);

void RefreshScaledMenuScreen_020b5a80(void)
{
    ScaledMenu *menu = data_ov023_020b6f64;
    ScreenInfo *screen = func_ov001_0207123c();
    void *tileMap = func_ov027_020b9df0(screen, 0x1b);
    s32 matrix[4];
    u16 *screenData;
    u32 tilesWide;
    u32 tilesHigh;

    matrix[0] = func_02023dbc(0x1000, menu->scale);
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = matrix[0];
    if (menu->needsLoad && !menu->loaded) {
        func_02007be0(menu->image->data, 0, menu->image->size);
        screenData = menu->screenData;
        tilesWide = (u32)screenData[0] >> 3;
        tilesHigh = (u32)screenData[1] >> 3;
        CopyClippedScreenRegion_020167d0(tileMap, screenData, 0, 0, 0, 0, screen->width, screen->height, tilesWide, tilesHigh);
        func_02007860(tileMap, 0, tilesWide * tilesHigh);
        menu->loaded = TRUE;
    }
    if (menu->needsRefresh) {
        func_020067b0((void *)0x04001030, matrix, 0, 0, menu->centerX, menu->centerY);
        func_0204f12c(menu->spriteManager);
        menu->needsRefresh = FALSE;
    }
}
