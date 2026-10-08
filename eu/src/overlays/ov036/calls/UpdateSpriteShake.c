#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShakeSprite {
    u8 pad_00[0x10];
    fx32 x;
    fx32 y;
    u8 pad_18[0x30];
    fx32 offset;
    fx32 amplitude;
    fx32 baseX;
    fx32 baseY;
    BOOL towardPositive;
    u8 pad_5C[0x4];
    s32 decayDivisor;
    u8 pad_64[0x24];
    u16 flags;
} ShakeSprite;

typedef struct SlotScene {
    u8 pad_0000[0xc80];
    s32 skipAnimation;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;
extern int _s32_div_f(int numerator, int denominator);

void UpdateSpriteShake(ShakeSprite *sprite)
{
    fx32 delta;

    if (sprite->towardPositive != 0) {
        delta = sprite->amplitude - sprite->offset;
    } else {
        delta = -(sprite->amplitude + sprite->offset);
    }
    sprite->offset += (fx32)(((s64)delta * 0x800 + 0x800) >> 12);
    sprite->towardPositive = sprite->towardPositive == 0;
    sprite->amplitude -= _s32_div_f(0x8000, sprite->decayDivisor);
    sprite->x = sprite->baseX + sprite->offset;
    sprite->y = sprite->baseY + (sprite->offset >> 1);
    if (data_ov036_020c3940.scene->skipAnimation == 0 && sprite->amplitude >= 0x29) {
        return;
    }
    sprite->x = sprite->baseX;
    sprite->y = sprite->baseY;
    sprite->flags &= ~2;
}
