#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitFieldOverlayState_020ba3e0(void);
extern void ReleaseFieldContext_020ba60c(void);

void *data_ov028_020bb304[5] = {
    (void *)0x0002000E,
    (void *)InitFieldOverlayState_020ba3e0,
    (void *)ReleaseFieldContext_020ba60c,
    (void *)0x00000024,
    NULL,
};

u32 data_ov028_020bb300[1] = {
    0xFFFFFFFF,
};
