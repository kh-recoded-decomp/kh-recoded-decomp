#include "nitro/types.h"

extern void *func_0202a178(u32 size);

typedef struct {
    u8 pad_000[0x1cc];
    void *pool2;
    u8 pad_1d0[0x10];
    s16 pool2Capacity;
    u16 pool2Count;
} PoolManager;

void InitPool2_020a4158(PoolManager *manager, s32 capacity)
{
    manager->pool2Capacity = (s16)capacity;
    manager->pool2Count = 0;
    manager->pool2 = func_0202a178(capacity * 0x28);
}
