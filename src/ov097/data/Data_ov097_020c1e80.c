#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyMenuScene_020beda8(void);
extern void InitMenuScene_020beb00(void);
extern void ScrollEntryCursorDown_020bf0b4(void);
extern void ScrollEntryCursorUp_020bef14(void);
extern void ScrollEntryListDown_020bf2f4(void);
extern void ScrollEntryListUp_020bf240(void);
extern void ToggleListMode_020bf400(void);
extern void UpdateMenuScene_020bedfc(void);
extern void func_ov097_020bf3a8(void);
extern void func_ov097_020bf3d0(void);

void *data_ov097_020c1e80[17] = {
    (void *)InitMenuScene_020beb00,
    (void *)DestroyMenuScene_020beda8,
    (void *)UpdateMenuScene_020bedfc,
    (void *)0x00000007,
    (void *)0x0000F0D0,
    (void *)ScrollEntryCursorUp_020bef14,
    (void *)ScrollEntryCursorDown_020bf0b4,
    (void *)ScrollEntryListUp_020bf240,
    (void *)ScrollEntryListDown_020bf2f4,
    NULL,
    (void *)func_ov097_020bf3a8,
    (void *)ToggleListMode_020bf400,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)func_ov097_020bf3d0,
};
