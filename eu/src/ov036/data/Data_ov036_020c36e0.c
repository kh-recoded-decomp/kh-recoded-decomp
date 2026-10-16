#include "src/overlays/ov036/Event2DPanel.h"

#pragma explicit_zero_data on

extern void ShutdownSceneWork_020ba6c4(void);

void *data_ov036_020c36e4[5] = {
    (void *)0x0002000E,
    (void *)InitEvent2DPanel,
    (void *)ShutdownSceneWork_020ba6c4,
    (void *)0x000010FC,
    NULL,
};

u32 data_ov036_020c36e0[1] = {
    0xFFFFFFFF,
};
