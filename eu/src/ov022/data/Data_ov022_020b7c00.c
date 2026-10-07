#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitMovieOverlayState(void);
extern void func_ov022_020a7020(void);

void *data_ov022_020b7c04[5] = {
    (void *)0x000D0008,
    (void *)func_ov022_020a7020,
    (void *)InitMovieOverlayState,
    (void *)0x00000AD4,
    NULL,
};

u32 data_ov022_020b7c00[1] = {
    0xFFFFFFFF,
};
