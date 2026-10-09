#include "nitro/types.h"

#pragma explicit_zero_data on

extern void MSL_FpInitA(void);
extern void func_020289c0(void);

void *gManagerObjectDescriptorA[5] = {
    (void *)0x00110011,
    (void *)func_020289c0,
    (void *)MSL_FpInitA,
    NULL,
    NULL,
};
