#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Pool2Entry {
    u32 kind;
    VecFx32 direction;
    u8 pad_10[0xc];
    fx32 scale;
} Pool2Entry;

typedef struct PoolOwner {
    u8 pad_00[0x38];
    VecFx32 position;
} PoolOwner;

typedef struct TargetResult {
    u32 status;
    VecFx32 position;
} TargetResult;

extern Pool2Entry *GetPool2Entry_020a41d4(PoolOwner *owner, int index);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void ComputePool2Target_020a43ec(TargetResult *result, PoolOwner *owner, int index)
{
    Pool2Entry *entry = GetPool2Entry_020a41d4(owner, index);
    VecFx32 target;

    VEC_MultAdd_01ffa09c(entry->scale, &entry->direction, &owner->position, &target);
    result->position = target;
    result->status = 0;
}
