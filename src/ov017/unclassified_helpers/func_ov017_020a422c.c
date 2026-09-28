#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1ec];
    u32 unk_1ec;
} PoolManager;

void func_ov017_020a422c(PoolManager *manager, u32 value)
{
    manager->unk_1ec = value;
}
