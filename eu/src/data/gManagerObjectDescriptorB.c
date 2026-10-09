#include "nitro/types.h"

#pragma explicit_zero_data on

extern void MSL_FpInitB(void);
extern void func_02028b30(void);

void *gManagerObjectDescriptorB[5] = {
    (void *)0x0011001D,
    (void *)func_02028b30,
    (void *)MSL_FpInitB,
    NULL,
    NULL,
};
