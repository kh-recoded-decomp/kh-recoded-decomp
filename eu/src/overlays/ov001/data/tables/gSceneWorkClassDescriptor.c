#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitSceneWork(void);
extern void ShutdownSceneWork(void);

void *gSceneWorkClassDescriptor[5] = {
    (void *)0x0007000F,
    (void *)InitSceneWork,
    (void *)ShutdownSceneWork,
    (void *)0x0000021C,
    NULL,
};
