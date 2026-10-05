#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyScreenState_020b6ac4(void);
extern void InitMapMenuState_020b6a18(void);

void *data_ov023_020b6f0c[5] = {
    (void *)0x000E0019,
    (void *)InitMapMenuState_020b6a18,
    (void *)DestroyScreenState_020b6ac4,
    (void *)0x00007FC4,
    NULL,
};
