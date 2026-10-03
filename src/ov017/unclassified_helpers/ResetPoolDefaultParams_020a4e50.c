#include "nitro/types.h"

typedef struct PoolParams {
    u32 words[5];
} PoolParams;

typedef struct ParamOwner {
    u8 pad_000[0x174];
    PoolParams params[4];
} ParamOwner;

extern PoolParams data_ov017_020a5e14;
extern PoolParams data_ov017_020a5e28;
extern PoolParams data_ov017_020a5e3c;
extern void MIi_CpuCopy32_01ff8710(const void *src, void *dest, u32 size);

void ResetPoolDefaultParams_020a4e50(ParamOwner *owner)
{
    PoolParams first = data_ov017_020a5e14;
    PoolParams second = data_ov017_020a5e28;
    PoolParams third = {0};
    PoolParams fourth = data_ov017_020a5e3c;

    MIi_CpuCopy32_01ff8710(&first, &owner->params[0], sizeof(PoolParams));
    MIi_CpuCopy32_01ff8710(&second, &owner->params[1], sizeof(PoolParams));
    MIi_CpuCopy32_01ff8710(&third, &owner->params[2], sizeof(PoolParams));
    MIi_CpuCopy32_01ff8710(&fourth, &owner->params[3], sizeof(PoolParams));
}
