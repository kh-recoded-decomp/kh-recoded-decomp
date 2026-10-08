#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CreatePartyState(void);
extern void func_ov001_0206cbb8(void);

#define DestroyEventContext func_ov001_0206cbb8

void *gPartyStateClassDescriptor[5] = {
    (void *)0x00070009,
    (void *)CreatePartyState,
    (void *)DestroyEventContext,
    (void *)0x00000100,
    NULL,
};
