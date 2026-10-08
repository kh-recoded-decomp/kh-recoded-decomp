#include "nitro/types.h"

#pragma explicit_zero_data on

extern void EnterWorldSession(void);
extern void ExitWorldSession(void);

void *gWorldSessionDescriptor[5] = {
    (void *)0x000E0008,
    (void *)EnterWorldSession,
    (void *)ExitWorldSession,
    (void *)0x00000008,
    NULL,
};
