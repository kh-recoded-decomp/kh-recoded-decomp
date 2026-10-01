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

extern FieldSpriteSet *data_ov001_020a049c;
extern void func_ov021_020a74f0(void *cell);

void SetFieldSpritesFlag_0206e53c(BOOL enable)
{
    FieldSpriteSet *set = data_ov001_020a049c;
    int i;

    if (set != NULL) {
        for (i = 0; i < set->spriteCount; i++) {
            FieldSprite *sprite = &set->sprites[i];

            if (enable) {
                sprite->flags |= 0x20;
            } else {
                sprite->flags &= ~0x20;
            }
            func_ov021_020a74f0(sprite->cell);
        }
    }
}
