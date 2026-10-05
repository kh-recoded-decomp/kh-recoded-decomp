#include "nitro/types.h"

#pragma explicit_zero_data on

extern void HandleRootMenuCancel_020c57dc(void);
extern void ReleaseRootMenu_020c4fa4(void);
extern void SelectNextRootMenuItem_020c5550(void);
extern void SelectPreviousRootMenuItem_020c54f0(void);
extern void ToggleRootMenuOptionLeft_020c55bc(void);
extern void ToggleRootMenuOptionRight_020c55f4(void);
extern void UpdateRootMenuFrame_020c4ed8(void);
extern void func_ov074_020c4260(void);
extern void func_ov074_020c562c(void);

void *data_ov074_020c5980[17] = {
    (void *)func_ov074_020c4260,
    (void *)ReleaseRootMenu_020c4fa4,
    (void *)UpdateRootMenuFrame_020c4ed8,
    NULL,
    (void *)0x000005E8,
    (void *)SelectPreviousRootMenuItem_020c54f0,
    (void *)SelectNextRootMenuItem_020c5550,
    (void *)ToggleRootMenuOptionLeft_020c55bc,
    (void *)ToggleRootMenuOptionRight_020c55f4,
    (void *)func_ov074_020c562c,
    (void *)HandleRootMenuCancel_020c57dc,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)HandleRootMenuCancel_020c57dc,
};
