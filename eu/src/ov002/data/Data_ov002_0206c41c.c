#include "nitro/types.h"

#pragma explicit_zero_data on

extern void StartScreenFade(void);
extern void MarkScreenFadeComplete(void);

void *gOv002ScreenFadeTaskClass[5] = {
    (void *)0x00100008,
    (void *)StartScreenFade,
    (void *)MarkScreenFadeComplete,
    (void *)0x0000000C,
    NULL,
};

u32 gOv002ScreenFadeCompleteStorage[1] = {
    0x00000001,
};
