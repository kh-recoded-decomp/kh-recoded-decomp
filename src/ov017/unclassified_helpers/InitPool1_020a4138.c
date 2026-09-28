#include "nitro/types.h"

extern void *func_0202a178(u32 size);

typedef struct {
    u8 pad_000[0x1c8];
    void *pool1;
    u8 pad_1cc[0x10];
    s16 pool1Capacity;
    u16 pool1Count;
} PoolManager;

void InitPool1_020a4138(PoolManager *manager, s32 capacity)
{
    manager->pool1Capacity = (s16)capacity;
    manager->pool1Count = 0;
    manager->pool1 = func_0202a178(capacity * 0x14);
}
