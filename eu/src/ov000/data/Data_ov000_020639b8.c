#include "nitro/types.h"

#pragma explicit_zero_data on

extern void func_ov000_02063680(void);
extern void func_ov000_020636c4(void);

u32 data_ov000_020639cc[13] = {
    0x00000000, 0x0000000E, 0x00000003, 0x00000004,
    0x00000005, 0x00000006, 0x00000007, 0x0000000F,
    0x0000000C, 0x00000010, 0x0000000D, 0x00000000,
    0x00000000,
};

void *data_ov000_020639b8[5] = {
    (void *)0x000E0008,
    (void *)func_ov000_02063680,
    (void *)func_ov000_020636c4,
    (void *)0x00000008,
    NULL,
};
