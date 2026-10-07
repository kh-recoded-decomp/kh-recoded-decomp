#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyPanelScene(void);
extern void SwitchToSecondaryIfEntryRejected(void);
extern void func_ov087_020c4694(void);
extern void func_ov087_020c715c(void);
extern void func_ov087_020c7510(void);

void *data_ov087_020c7da0[17] = {
    (void *)func_ov087_020c715c,
    (void *)DestroyPanelScene,
    (void *)func_ov087_020c7510,
    (void *)0x00000002,
    (void *)0x00000BE0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)func_ov087_020c4694,
    (void *)SwitchToSecondaryIfEntryRejected,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
