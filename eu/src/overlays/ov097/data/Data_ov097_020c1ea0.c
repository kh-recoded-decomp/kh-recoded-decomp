#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyMenuScene_020bedc8(void);
extern void InitMenuScene_020beb20(void);
extern void ScrollEntryCursorDown(void);
extern void ScrollEntryCursorUp(void);
extern void ScrollEntryListDown(void);
extern void ScrollEntryListUp(void);
extern void ToggleListMode(void);
extern void UpdateMenuScene(void);
extern void func_ov097_020bf3c8(void);
extern void func_ov097_020bf3f0(void);

void *gStoryReportCommandTable[17] = {
    (void *)InitMenuScene_020beb20,
    (void *)DestroyMenuScene_020bedc8,
    (void *)UpdateMenuScene,
    (void *)0x00000007,
    (void *)0x0000F0D0,
    (void *)ScrollEntryCursorUp,
    (void *)ScrollEntryCursorDown,
    (void *)ScrollEntryListUp,
    (void *)ScrollEntryListDown,
    NULL,
    (void *)func_ov097_020bf3c8,
    (void *)ToggleListMode,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)func_ov097_020bf3f0,
};
