#include "nitro/types.h"

typedef struct {
    void *slots;
    s8 slotCount;
} EffectPool;

typedef struct {
    u8 pad_000[0x18c];
    EffectPool effectPool;
} EffectOwner;

extern void func_ov056_020d7e34(EffectPool *pool);

void ReleaseEffectPool_020d44ec(EffectOwner *owner)
{
    func_ov056_020d7e34(&owner->effectPool);
}
