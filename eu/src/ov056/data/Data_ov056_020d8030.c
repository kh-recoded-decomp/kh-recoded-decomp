#include "nitro/types.h"

#pragma explicit_zero_data on

extern void FreeSlotBuffers(void);
extern void FreeSlotBuffers_020d641c(void);
extern void FreeSlotBuffers_020d6788(void);
extern void FreeSlotBuffers_020d7060(void);
extern void FreeSlotBuffers_020d788c(void);
extern void ReleaseEffectPool(void);
extern void ReleaseEffectPool_020d450c(void);
extern void func_ov021_020af21c(void);
extern void func_ov056_020d4aa0(void);

void *data_ov056_020d8030[20] = {
    NULL,
    (void *)ReleaseEffectPool_020d450c,
    NULL,
    NULL,
    (void *)func_ov021_020af21c,
    (void *)FreeSlotBuffers,
    NULL,
    NULL,
    NULL,
    (void *)FreeSlotBuffers_020d641c,
    (void *)FreeSlotBuffers_020d641c,
    (void *)FreeSlotBuffers_020d6788,
    (void *)func_ov056_020d4aa0,
    (void *)func_ov021_020af21c,
    NULL,
    (void *)FreeSlotBuffers_020d7060,
    NULL,
    (void *)FreeSlotBuffers_020d788c,
    NULL,
    (void *)ReleaseEffectPool,
};
