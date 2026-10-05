#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitMovieOverlayState_020a722c(void);
extern void StartMoviePlaybackState_020a7000(void);

void *data_ov022_020b7be4[5] = {
    (void *)0x000D0008,
    (void *)StartMoviePlaybackState_020a7000,
    (void *)InitMovieOverlayState_020a722c,
    (void *)0x00000AD4,
    NULL,
};

u32 data_ov022_020b7be0[1] = {
    0xFFFFFFFF,
};
