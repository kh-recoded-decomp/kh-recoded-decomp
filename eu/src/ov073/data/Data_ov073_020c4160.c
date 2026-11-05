#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitStatusMenu(void);
extern void UpdateStatusMenu(void);
extern void DestroyStatusMenu(void);

void *data_ov073_020c4160[16] = {
    (void *)InitStatusMenu,
    (void *)DestroyStatusMenu,
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
