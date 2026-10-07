#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitBarGauge(void);
extern void func_ov035_020bc0e4(void);

void *gBarGaugeClassDescriptor[6] = {
    (void *)0x000E000C,
    (void *)InitBarGauge,
    (void *)func_ov035_020bc0e4,
    (void *)0x00000138,
    NULL,
    NULL,
};
