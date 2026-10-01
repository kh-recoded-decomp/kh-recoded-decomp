#include "nitro/types.h"

typedef struct Ov038Position {
    s32 x;
    s32 y;
} Ov038Position;

typedef struct Ov038Sprite {
    s32 recordIndex;
    s32 x;
    s32 y;
    s32 offsetX;
    s32 offsetY;
} Ov038Sprite;

typedef struct Ov038SpritePool {
    u8 data[0x6434];
} Ov038SpritePool;

typedef struct Ov038Context {
    u8 pad_00[0x40];
    Ov038SpritePool pools[2];
    Ov038Sprite topSprites[3];
    Ov038Sprite bottomSprites[3];
} Ov038Context;

extern Ov038Context *g_ov038Context_020bd144;
extern void func_0204f13c(void *recordBase, s32 recordIndex, Ov038Position *position);

void SetOv038SpriteOffset_020bb2ac(s32 poolIndex, s32 spriteIndex, s32 offsetX, s32 offsetY)
{
    Ov038Context *context = g_ov038Context_020bd144;
    Ov038SpritePool *pool = &context->pools[poolIndex];
    Ov038Sprite *sprite;
    Ov038Position position;

    if (poolIndex == 0) {
        sprite = &context->topSprites[spriteIndex];
    } else {
        sprite = &context->bottomSprites[spriteIndex];
    }
    sprite->offsetX = offsetX;
    sprite->offsetY = offsetY;
    position.x = (sprite->x + offsetX) * 0x1000;
    position.y = (sprite->y + sprite->offsetY) * 0x1000;
    func_0204f13c(pool, sprite->recordIndex, &position);
}
