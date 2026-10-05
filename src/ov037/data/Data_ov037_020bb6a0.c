#include "nitro/types.h"

#pragma explicit_zero_data on

extern void BeginCommSession_020ba3e0(void);
extern void ShutdownCommChannelAndAudio_020ba4e4(void);

void *data_ov037_020bb6a4[5] = {
    (void *)0x0002000E,
    (void *)BeginCommSession_020ba3e0,
    (void *)ShutdownCommChannelAndAudio_020ba4e4,
    (void *)0x00000024,
    NULL,
};

u32 data_ov037_020bb6a0[1] = {
    0xFFFFFFFF,
};
