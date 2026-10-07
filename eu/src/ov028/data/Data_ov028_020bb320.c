#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitFieldOverlayState(void);
extern void ReleaseFieldContext(void);

void *data_ov028_020bb324[5] = {
    (void *)0x0002000E,
    (void *)InitFieldOverlayState,
    (void *)ReleaseFieldContext,
    (void *)0x00000024,
    NULL,
};

u32 data_ov028_020bb320[1] = {
    0xFFFFFFFF,
};
