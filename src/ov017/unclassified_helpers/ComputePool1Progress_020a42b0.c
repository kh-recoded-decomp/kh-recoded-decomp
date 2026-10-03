#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Pool1Entry {
    u32 id : 16;
    s32 type : 16;
    VecFx32 point;
    fx32 value;
} Pool1Entry;

typedef struct PoolOwner {
    u8 pad_00[0x38];
    VecFx32 position;
} PoolOwner;

typedef struct ProgressResult {
    u32 status;
    fx32 progress;
    VecFx32 position;
} ProgressResult;

extern Pool1Entry *GetPool1Entry_020a41c4(PoolOwner *owner, int index);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern int FX_Div_01ff9c84(int numer, int denom);

void ComputePool1Progress_020a42b0(ProgressResult *result, PoolOwner *owner, int index)
{
    Pool1Entry *entry = GetPool1Entry_020a41c4(owner, index);

    result->status = 0;
    result->position = owner->position;
    switch (entry->type) {
    case 0:
        result->progress = entry->value;
        break;
    case 1:
        result->progress = FX_Div_01ff9c84(func_01ffa0f4(&result->position, &entry->point), entry->value);
        break;
    }
}
