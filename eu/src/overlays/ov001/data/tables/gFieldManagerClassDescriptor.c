#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitFieldManager(void);
extern void ShutdownFieldScene(void);

void *gFieldManagerClassDescriptor[5] = {
    (void *)0x000E001B,
    (void *)InitFieldManager,
    (void *)ShutdownFieldScene,
    (void *)0x00001358,
    NULL,
};
