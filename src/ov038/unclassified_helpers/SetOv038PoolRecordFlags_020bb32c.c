#include "nitro/types.h"

typedef struct Ov038SpritePool {
    u8 data[0x6434];
} Ov038SpritePool;

typedef struct Ov038Context {
    u8 pad_00[0x40];
    Ov038SpritePool pools[2];
} Ov038Context;

extern Ov038Context *g_ov038Context_020bd144;
extern void func_0204f204(void *pool, s32 recordIndex, u16 value);

void SetOv038PoolRecordFlags_020bb32c(s32 poolIndex, s32 recordIndex, int value)
{
    func_0204f204(&g_ov038Context_020bd144->pools[poolIndex], recordIndex, value);
}
