#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ShutdownPopupSystem(void);
extern void InitPopupManager(void);

void *gTrophyPopupTaskDescriptorStorage[10] = {
    (void *)0x000E001B,
    (void *)InitPopupManager,
    (void *)ShutdownPopupSystem,
    (void *)0x00000270,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
