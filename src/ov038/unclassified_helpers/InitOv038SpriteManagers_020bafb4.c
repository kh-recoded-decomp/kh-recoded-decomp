#include "nitro/types.h"

typedef struct Ov038SpriteDesc {
    u8 data[0x1c];
} Ov038SpriteDesc;

typedef struct Ov038SpritePool {
    u8 data[0x6434];
} Ov038SpritePool;

typedef struct Ov038Context {
    u8 pad_00[0x04];
    u32 topVramOffset;
    u8 pad_08[0x04];
    u32 bottomVramOffset;
    u8 pad_10[0x30];
    Ov038SpritePool pools[2];
} Ov038Context;

typedef struct ObjManagerConfig {
    u32 vramKey;
    s32 mode;
    u32 reserved0;
    u32 reserved1;
} ObjManagerConfig;

extern Ov038Context *g_ov038Context_020bd144;
extern Ov038SpriteDesc g_ov038TopSprites_020bbdf8[];
extern Ov038SpriteDesc g_ov038BottomSprites_020bc654[];
extern void InitObjManager_0204efa8(Ov038SpritePool *pool, ObjManagerConfig *config);
extern void PXI_Init_0204f00c(Ov038SpritePool *pool, u32 vramKey);
extern void CreateOv038Sprite_020bb13c(s32 poolIndex, s32 spriteIndex, Ov038SpriteDesc *desc);

void InitOv038SpriteManagers_020bafb4(void)
{
    Ov038Context *ctx = g_ov038Context_020bd144;
    ObjManagerConfig config;
    Ov038SpritePool *bottomPool;
    s32 index;

    config.vramKey = ((ctx->topVramOffset + 0x8000) & 0xfffffc) << 7 | 0x80000003;
    config.mode = 1;
    config.reserved0 = 0;
    config.reserved1 = 0;
    InitObjManager_0204efa8(&ctx->pools[0], &config);
    for (index = 0; index < 3; index++) {
        CreateOv038Sprite_020bb13c(0, index, &g_ov038TopSprites_020bbdf8[index]);
    }
    config.vramKey = ((ctx->topVramOffset + 0x8000) & 0xfffffc) << 7 | 0x80000001;
    config.mode = 2;
    config.reserved0 = 0;
    config.reserved1 = 0;
    bottomPool = &ctx->pools[1];
    InitObjManager_0204efa8(bottomPool, &config);
    PXI_Init_0204f00c(bottomPool, ((ctx->bottomVramOffset + 0x8000) & 0xfffffc) << 7 | 0x80000000);
    for (index = 0; index < 99; index++) {
        CreateOv038Sprite_020bb13c(1, index, &g_ov038BottomSprites_020bc654[index]);
    }
}
