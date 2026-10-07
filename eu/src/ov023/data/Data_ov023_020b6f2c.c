#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyScreenState(void);
extern void InitMapMenuState(void);

void *data_ov023_020b6f2c[5] = {
    (void *)0x000E0019,
    (void *)InitMapMenuState,
    (void *)DestroyScreenState,
    (void *)0x00007FC4,
    NULL,
};
