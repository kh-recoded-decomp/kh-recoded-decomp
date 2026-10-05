#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitMenuScreen_020b5acc(void);
extern void ShutdownMenuScreen_020b5e8c(void);

void *data_ov025_020b7728[5] = {
    (void *)0x000E0018,
    (void *)InitMenuScreen_020b5acc,
    (void *)ShutdownMenuScreen_020b5e8c,
    (void *)0x000066DC,
    NULL,
};
