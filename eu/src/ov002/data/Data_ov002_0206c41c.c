#include "nitro/types.h"

#pragma explicit_zero_data on

extern void StartScreenFade(void);
extern void MarkScreenFadeComplete(void);

void *data_ov002_0206c420[5] = {
    (void *)0x00100008,
    (void *)StartScreenFade,
    (void *)MarkScreenFadeComplete,
    (void *)0x0000000C,
    NULL,
};

u32 data_ov002_0206c41c[1] = {
    0x00000001,
};
