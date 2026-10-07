#include "nitro/types.h"

#pragma explicit_zero_data on

extern void BeginOverlayDisplaySession(void);
extern void EndOverlayDisplaySession(void);

void *data_ov026_020b5ae0[5] = {
    (void *)0x000E0019,
    (void *)BeginOverlayDisplaySession,
    (void *)EndOverlayDisplaySession,
    (void *)0x0000649C,
    NULL,
};
