#include "nitro/types.h"

#pragma explicit_zero_data on

extern void BeginCommSession(void);
extern void ShutdownCommChannelAndAudio(void);

void *gOv037SceneTaskClass[5] = {
    (void *)0x0002000E,
    (void *)BeginCommSession,
    (void *)ShutdownCommChannelAndAudio,
    (void *)0x00000024,
    NULL,
};

u32 gOv037SceneTaskHandle[1] = {
    0xFFFFFFFF,
};
