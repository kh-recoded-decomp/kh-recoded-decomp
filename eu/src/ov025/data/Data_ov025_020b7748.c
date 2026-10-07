#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitMenuScreen(void);
extern void ShutdownMenuScreen(void);

void *data_ov025_020b7748[5] = {
    (void *)0x000E0018,
    (void *)InitMenuScreen,
    (void *)ShutdownMenuScreen,
    (void *)0x000066DC,
    NULL,
};
