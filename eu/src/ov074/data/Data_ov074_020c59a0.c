#include "nitro/types.h"

#pragma explicit_zero_data on

extern void HandleRootMenuCancel(void);
extern void ReleaseRootMenu(void);
extern void SelectNextRootMenuItem(void);
extern void SelectPreviousRootMenuItem(void);
extern void ToggleRootMenuOptionLeft(void);
extern void ToggleRootMenuOptionRight(void);
extern void func_ov074_020c4280(void);
extern void func_ov074_020c4ef8(void);
extern void func_ov074_020c564c(void);

void *data_ov074_020c59a0[17] = {
    (void *)func_ov074_020c4280,
    (void *)ReleaseRootMenu,
    (void *)func_ov074_020c4ef8,
    NULL,
    (void *)0x000005E8,
    (void *)SelectPreviousRootMenuItem,
    (void *)SelectNextRootMenuItem,
    (void *)ToggleRootMenuOptionLeft,
    (void *)ToggleRootMenuOptionRight,
    (void *)func_ov074_020c564c,
    (void *)HandleRootMenuCancel,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)HandleRootMenuCancel,
};
