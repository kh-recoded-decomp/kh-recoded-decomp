#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitMovieOverlayState(void);
extern void StartMoviePlaybackState(void);

void *data_ov022_020b7c04[5] = {
    (void *)0x000D0008,
    (void *)StartMoviePlaybackState,
    (void *)InitMovieOverlayState,
    (void *)0x00000AD4,
    NULL,
};

u32 data_ov022_020b7c00[1] = {
    0xFFFFFFFF,
};
