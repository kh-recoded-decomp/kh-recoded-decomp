#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    fx32 texLeft;
    fx32 texRight;
    fx32 texTop;
    fx32 texBottom;
    fx32 x;
    fx32 y;
    fx32 z;
    fx32 width;
    fx32 height;
    fx32 scale;
    MtxFx33 rotation;
    u16 color;
    const u32 *texParams;
} SpriteQuad;

typedef struct {
    u8 pad_0000[0x6b0];
    u32 gaugeTextureParams[2];
    u8 pad_06b8[0x4db8 - 0x6b8];
    u32 scrollOffset;
} SlotMenuGaugeScreen;

extern void DrawSpriteQuad_020c9808(const SpriteQuad *quad);

void DrawSlotMenuGaugeAndDigits(SlotMenuGaugeScreen *menu, int row, u32 value, u32 maxValue, int posX)
{
    SpriteQuad quad;
    int count;
    u32 filled;
    int digit;
    int column;
    int line;

    quad.scale = FX32_ONE;
    quad.rotation._00 = quad.rotation._11 = quad.rotation._22 = FX32_ONE;
    quad.z = 0x400000;
    quad.texParams = menu->gaugeTextureParams;
    count = 0;
    quad.color = 0x7fff;
    quad.x = posX << FX32_SHIFT;
    quad.rotation._01 = quad.rotation._02 = quad.rotation._10 = quad.rotation._12 = quad.rotation._20 =
        quad.rotation._21 = 0;
    quad.height = 0x8000;
    quad.y = 0xc0000 - ((row * 16 + 0x22 - (menu->scrollOffset & 0xf)) << FX32_SHIFT);
    if (value != 0 && (filled = value * 14 / maxValue) != 0) {
        quad.width = filled << FX32_SHIFT;
        quad.x = quad.x + FX32_ONE;
        quad.texLeft = FX32_ONE;
        quad.texRight = quad.width;
        quad.texTop = 0x8000;
        quad.texBottom = 0x10000;
        DrawSpriteQuad_020c9808(&quad);
        quad.x -= FX32_ONE;
    }
    quad.texLeft = 0;
    quad.texTop = 0;
    quad.width = 0x10000;
    quad.texRight = 0x10000;
    quad.texBottom = 0x8000;
    DrawSpriteQuad_020c9808(&quad);
    quad.y -= 0x6000;
    quad.width = 0x8000;
    quad.x = (posX + 10) << FX32_SHIFT;
    quad.height = 0x8000;
    do {
        digit = value % 10;
        column = (digit % 5) * 8 + 0x10;
        line = (digit >= 5) * 8;
        quad.texLeft = column << FX32_SHIFT;
        quad.texRight = (column + 8) << FX32_SHIFT;
        quad.texTop = line << FX32_SHIFT;
        quad.texBottom = (line + 8) << FX32_SHIFT;
        DrawSpriteQuad_020c9808(&quad);
        value /= 10;
        count++;
        quad.x -= 0x4000;
    } while (count < 4 && value != 0);
}
