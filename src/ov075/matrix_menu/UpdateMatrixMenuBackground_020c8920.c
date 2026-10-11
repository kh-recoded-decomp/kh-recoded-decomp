#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u16 rawData[1];
} ScreenData;

typedef struct CharacterData {
    u16 height;
    u16 width;
    u32 pixelFmt;
    u32 mappingType;
    u32 characterFmt;
    u32 szByte;
    void *pRawData;
} CharacterData;

typedef struct MatrixMenu {
    u8 pad_00000[8];
    u8 redraw;
    u8 pad_00009[0x34 - 9];
    fx32 posX;
    fx32 posY;
    s16 bgX;
    s16 bgY;
    u8 pad_00040[8];
    u32 frameParity;
    u8 pad_0004c[0x70 - 0x4c];
    s32 mapOpen;
    u8 pad_00074[0x12dbc - 0x74];
    ScreenData *matrixScreen;
    u8 pad_12dc0[0x131a8 - 0x12dc0];
    s32 blinkTimer;
    u8 pad_131ac[0x13ed4 - 0x131ac];
    ScreenData *mapScreen;
    CharacterData *mapChars;
    u8 pad_13edc[0x174e0 - 0x13edc];
    void *matrixChars;
    u8 pad_174e4[0x1752d - 0x174e4];
    u8 toonUpdates;
    u8 pulse;
    u8 pad_1752f;
    s32 pulseRising;
    u16 toonTable[32];
} MatrixMenu;

extern MatrixMenu *data_ov075_020d18e0;

extern u32 func_01ff80d4(void);
extern void *G2_GetBG3ScrPtr_02006f80(void);
extern void *G2_GetBG3CharPtr_020071b0(void);
extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);
extern void G3X_SetToonTable_02006bf0(const u16 *table);

static inline void CopyFast(const void *src, void *dst, u32 size)
{
    MIi_CpuCopyFast_01ff878c(src, dst, size);
}

static inline s16 AbsS16(s16 value)
{
    s16 sign = value >> 15;
    return (u16)((value ^ sign) - sign);
}

void UpdateMatrixMenuBackground_020c8920(void)
{
    MatrixMenu *menu = data_ov075_020d18e0;
    u16 *screen;
    u16 *dst;
    u16 *src;
    s16 scrollX;
    s16 scrollY;
    s16 alignedX;
    s16 alignedY;
    s16 deltaX;
    s16 deltaY;
    s16 tiles;
    u16 width;
    s16 stride;
    s16 row;
    s16 col;
    u8 pulse;
    u16 level;
    u16 third;
    int color;
    int blue;

    if (((menu->frameParity ^ func_01ff80d4()) & 1) == 0) {
        if (menu->mapOpen != 0) {
            if (menu->redraw) {
                CopyFast(menu->mapScreen->rawData, G2_GetBG3ScrPtr_02006f80(), menu->mapScreen->szByte);
                CopyFast(menu->mapChars->pRawData, G2_GetBG3CharPtr_020071b0(), menu->mapChars->szByte);
                *(vu32 *)0x0400001c = 0;
                menu->redraw = 0;
            }
        } else {
            if (menu->redraw) {
                CopyFast(menu->matrixChars, G2_GetBG3CharPtr_020071b0(), menu->mapChars->szByte);
            }
            scrollX = (s16)(menu->posX >> 12);
            scrollY = (s16)(menu->posY >> 12);
            deltaX = AbsS16(scrollX - menu->bgX);
            deltaY = AbsS16(scrollY - menu->bgY);
            if (deltaX >= 8 || deltaY >= 8 || menu->redraw) {
                screen = G2_GetBG3ScrPtr_02006f80();
                width = menu->matrixScreen->screenWidth;
                dst = screen + 0x3e0;
                tiles = width >> 3;
                alignedX = scrollX & 0xfff8;
                menu->bgX = alignedX;
                alignedY = scrollY & 0xfff8;
                menu->bgY = alignedY;
                src = menu->matrixScreen->rawData + (alignedY >> 3) * tiles + (alignedX >> 3);
                dst[0x41f] = *src++;
                for (col = 32; col > 0; col--) {
                    *dst++ = *src++;
                }
                dst[0x3e0] = *src++;
                stride = tiles - 34;
                src += stride;
                dst = screen;
                for (row = 25; row > 0; row--) {
                    dst[0x41f] = *src++;
                    for (col = 32; col > 0; col--) {
                        *dst++ = *src++;
                    }
                    dst[0x3e0] = *src++;
                    src += stride;
                }
            }
            *(vu32 *)0x0400001c = (-(menu->bgX - (menu->posX >> 12)) & 0x1ff)
                                | ((-(menu->bgY - (menu->posY >> 12)) << 16) & 0x1ff0000);
        }

        if (menu->pulseRising == 0 && ++menu->pulse == 30) {
            menu->pulseRising = 1;
        } else if (menu->pulseRising != 0 && --menu->pulse == 0) {
            menu->pulseRising = 0;
        }
        pulse = menu->pulse;
        level = pulse >> 1;
        color = level | (level << 5);
        menu->toonTable[27] = color;
        menu->toonTable[28] = (level << 10) | color;
        third = pulse / 3;
        menu->toonTable[29] = (third << 10) | (third | (third << 5));
        blue = level / 3;
        menu->toonTable[30] = (blue << 10) | color;
        menu->toonTable[31] = (level << 10) | (blue | (blue << 5));
        G3X_SetToonTable_02006bf0(menu->toonTable);
        menu->toonUpdates++;
    }
    if (++menu->blinkTimer == 30) {
        menu->blinkTimer = 0;
    }
}
