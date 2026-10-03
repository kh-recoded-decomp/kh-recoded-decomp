#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShakeLayer {
    fx32 offset;
    fx32 amplitude;
    fx32 baseX;
    fx32 baseY;
    BOOL towardPositive;
    u8 pad_14[0x10];
    u16 flags;
    u8 pad_26[0x1a];
    s32 verticalBias;
    u8 pad_44[0x4];
    s32 decayDivisor;
} ShakeLayer;

typedef struct SlotScene {
    u8 pad_0000[0xc80];
    s32 skipAnimation;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3920;
extern int func_02023dbc(int numerator, int denominator);

#define REG_BG1OFS (*(vu32 *)0x04000014)
#define REG_DB_BG0OFS (*(vu32 *)0x04001010)

void UpdateLayerShake_020bbd20(ShakeLayer *layer, BOOL subScreen)
{
    fx32 delta;
    s32 divisor;
    int x;
    int y;
    fx32 offset;
    fx32 baseX;
    fx32 baseY;

    if (layer->towardPositive != 0) {
        delta = layer->amplitude - layer->offset;
    } else {
        delta = -(layer->amplitude + layer->offset);
    }
    layer->offset += (fx32)(((s64)delta * 0x800 + 0x800) >> 12);
    divisor = layer->decayDivisor;
    layer->towardPositive = layer->towardPositive == 0;
    if (divisor != -1) {
        if (divisor == 0) {
            layer->amplitude = 0;
        } else {
            layer->amplitude -= func_02023dbc(0x8000, divisor);
        }
    }
    offset = layer->offset;
    baseX = layer->baseX;
    baseY = layer->baseY;
    x = (baseX + offset) >> 12;
    y = (baseY + offset) >> 12;
    if (data_ov036_020c3920.scene->skipAnimation != 0 || layer->amplitude < 0x29) {
        layer->flags &= ~0x30;
        x = baseX >> 12;
        y = baseY >> 12;
    }
    if (subScreen == 0) {
        REG_BG1OFS = (-x & 0x1ff) | ((-(y - layer->verticalBias) << 16) & 0x1ff0000);
    } else {
        REG_DB_BG0OFS = (-x & 0x1ff) | ((-y << 16) & 0x1ff0000);
    }
}
