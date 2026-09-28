#include "nitro/types.h"

extern void *func_0202a178(u32 size);

typedef struct {
    u8 pad_000[0x1d4];
    void *pool4;
    u8 pad_1d8[0x10];
    s16 pool4Capacity;
    u16 pool4Count;
} PoolManager;

void InitPool4_020a4198(PoolManager *manager, s32 capacity)
{
    manager->pool4Capacity = (s16)capacity;
    manager->pool4Count = 0;
    manager->pool4 = func_0202a178(capacity << 2);
}
