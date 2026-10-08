#include "nitro/types.h"

typedef struct FieldSprite {
    u8 pad_00[8];
    u8 cell[0x1c];
    u16 flags;
    u8 pad_26[2];
} FieldSprite;

typedef struct FieldSpriteSet {
    u32 unk_00;
    FieldSprite sprites[3];
    int spriteCount;
} FieldSpriteSet;

extern FieldSpriteSet *data_ov001_020a04bc;
extern void func_ov021_020a7510(void *cell);

void SetFieldSpritesFlag(BOOL enable)
{
    FieldSpriteSet *set = data_ov001_020a04bc;
    int i;

    if (set != NULL) {
        for (i = 0; i < set->spriteCount; i++) {
            FieldSprite *sprite = &set->sprites[i];

            if (enable) {
                sprite->flags |= 0x20;
            } else {
                sprite->flags &= ~0x20;
            }
            func_ov021_020a7510(sprite->cell);
        }
    }
}
