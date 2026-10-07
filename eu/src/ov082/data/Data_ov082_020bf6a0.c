#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ShutdownOv082Screen(void);
extern void func_ov082_020beac0(void);
extern void func_ov082_020bf390(void);

void *data_ov082_020bf6a0[16] = {
    (void *)func_ov082_020beac0,
    (void *)ShutdownOv082Screen,
    (void *)func_ov082_020bf390,
    (void *)0x0000372C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
