#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CreatePartyState(void);
extern void ReleaseEventContextWork(void);

#define DestroyEventContext ReleaseEventContextWork

void *gPartyStateClassDescriptor[5] = {
    (void *)0x00070009,
    (void *)CreatePartyState,
    (void *)DestroyEventContext,
    (void *)0x00000100,
    NULL,
};
