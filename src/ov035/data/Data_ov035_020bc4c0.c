#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitBarGauge_020bc00c(void);
extern void func_ov035_020bc0c4(void);

void *data_ov035_020bc4c8[6] = {
    (void *)0x000E000C,
    (void *)InitBarGauge_020bc00c,
    (void *)func_ov035_020bc0c4,
    (void *)0x00000138,
    NULL,
    NULL,
};

u32 data_ov035_020bc4c0[2] = {
    0x04B7006F, 0x0CFE04DA,
};
