#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitStatusMenu(void);
extern void UpdateStatusMenu(void);
extern void func_ov073_020bfbec(void);

void *data_ov073_020c4160[16] = {
    (void *)InitStatusMenu,
    (void *)func_ov073_020bfbec,
    (void *)UpdateStatusMenu,
    (void *)0x00001230,
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
