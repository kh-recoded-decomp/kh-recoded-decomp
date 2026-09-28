#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1ec];
    u32 unk_1ec;
} PoolManager;

u32 func_ov017_020a4234(PoolManager *manager)
{
    return manager->unk_1ec;
}
