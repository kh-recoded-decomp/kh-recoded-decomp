#include "nitro/types.h"

typedef struct Ov038SpriteDesc {
    s32 resourceA;
    s32 resourceB;
    s32 x;
    s32 y;
    u8 pad_10[0x04];
    BOOL markRecord;
    u32 priority;
} Ov038SpriteDesc;

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
extern s32 func_0204f0b4(Ov038SpritePool *pool, s32 resourceA, s32 resourceB);
extern void func_0204f204(Ov038SpritePool *pool, s32 recordIndex, s32 value);
extern void func_0204f2e4(Ov038SpritePool *pool, s32 recordIndex);
extern void Slot_SetMode2Bit_0204f480(Ov038SpritePool *pool, s32 recordIndex, s32 value);
extern void func_0204f378(Ov038SpritePool *pool, s32 recordIndex, s32 value);
extern void func_0204f178(Ov038SpritePool *pool, s32 recordIndex, s32 scale);
extern void func_0204f2c0(Ov038SpritePool *pool, s32 recordIndex);
extern void SetOv038SpritePosition_020bb230(s32 poolIndex, s32 spriteIndex, s32 x, s32 y);

void CreateOv038Sprite_020bb13c(s32 poolIndex, s32 spriteIndex, Ov038SpriteDesc *desc)
{
    Ov038Context *context = g_ov038Context_020bd144;
    Ov038SpritePool *pool = &context->pools[poolIndex];
    Ov038Sprite *sprite;
    s32 recordIndex;

    if (poolIndex == 0) {
        sprite = &context->topSprites[spriteIndex];
    } else {
        sprite = &context->bottomSprites[spriteIndex];
    }
    recordIndex = func_0204f0b4(pool, desc->resourceA, desc->resourceB);
    func_0204f204(pool, recordIndex, 0);
    func_0204f2e4(pool, recordIndex);
    Slot_SetMode2Bit_0204f480(pool, recordIndex, 0);
    func_0204f378(pool, recordIndex, 1);
    func_0204f178(pool, recordIndex, (u8)desc->priority);
    if (desc->markRecord != 0) {
        func_0204f2c0(pool, recordIndex);
    }
    sprite->recordIndex = recordIndex;
    sprite->x = desc->x;
    sprite->y = desc->y;
    sprite->offsetX = 0;
    sprite->offsetY = 0;
    SetOv038SpritePosition_020bb230(poolIndex, spriteIndex, desc->x, desc->y);
}
