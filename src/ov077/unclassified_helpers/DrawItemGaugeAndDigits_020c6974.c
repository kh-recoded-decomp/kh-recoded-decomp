#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct TexturedQuad {
    fx32 s0;
    fx32 s1;
    fx32 t0;
    fx32 t1;
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot;
    u16 color;
    u16 pad_4e;
    void *texParams;
} TexturedQuad;

typedef struct ItemScreen {
    u8 pad_0000[0x6b0];
    u8 texParams[0x4db8 - 0x6b0];
    u32 scrollOffset;
} ItemScreen;

extern void func_ov077_020c681c(TexturedQuad *quad);

void DrawItemGaugeAndDigits_020c6974(ItemScreen *screen, int row, u32 value, u32 maxValue, int column)
{
    TexturedQuad quad;
    int i = 0;
    int fill;
    int digit;
    int half;
    int col;

    quad.scale.z = FX32_ONE;
    quad.trans.z = FX32_ONE * 0x400;
    quad.texParams = screen->texParams;
    quad.color = 0x7fff;
    quad.trans.x = column << 12;
    quad.rot.m[2][2] = FX32_ONE;
    quad.rot.m[1][1] = FX32_ONE;
    quad.rot.m[0][0] = FX32_ONE;
    quad.rot.m[2][1] = 0;
    quad.rot.m[2][0] = 0;
    quad.rot.m[1][2] = 0;
    quad.rot.m[1][0] = 0;
    quad.rot.m[0][2] = 0;
    quad.rot.m[0][1] = 0;
    quad.scale.y = 0x8000;
    quad.trans.y = 0xc0000 - ((row * 16 + 0x22 - (screen->scrollOffset & 0xf)) << 12);
    if (value != 0) {
        fill = value * 14 / maxValue;
        if (fill != 0) {
            quad.scale.x = fill << 12;
            quad.trans.x += FX32_ONE;
            quad.s0 = FX32_ONE;
            quad.s1 = fill << 12;
            quad.t1 = 0x10000;
            quad.t0 = 0x8000;
            func_ov077_020c681c(&quad);
            quad.trans.x -= FX32_ONE;
        }
    }
    quad.s0 = 0;
    quad.t0 = 0;
    quad.scale.x = 0x10000;
    quad.s1 = 0x10000;
    quad.t1 = 0x8000;
    func_ov077_020c681c(&quad);
    quad.trans.y -= 0x6000;
    quad.scale.x = 0x8000;
    quad.trans.x = (column + 10) << 12;
    quad.scale.y = 0x8000;
    do {
        digit = value % 10;
        col = digit % 5 * 8 + 0x10;
        half = (digit >= 5 ? 1 : 0) * 8;
        quad.s0 = col << 12;
        quad.s1 = (col + 8) << 12;
        quad.t0 = half << 12;
        quad.t1 = (half + 8) << 12;
        func_ov077_020c681c(&quad);
        value /= 10;
        quad.trans.x -= 0x4000;
    } while (++i < 4 && value != 0);
}
