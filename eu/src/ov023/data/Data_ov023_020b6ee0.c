#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyResourceCache(void);
extern void InitMenuResourceCache(void);

void *gMenuResourceCacheTaskClass[5] = {
    (void *)0x000E0018,
    (void *)InitMenuResourceCache,
    (void *)DestroyResourceCache,
    (void *)0x00000040,
    NULL,
};
