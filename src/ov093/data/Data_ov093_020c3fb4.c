#include "nitro/types.h"

#pragma explicit_zero_data on

extern void FinishGridPageScrollDual_020bf028(void);
extern void FinishGridPageScroll_020bee3c(void);
extern void InitEntryGridScene_020beb20(void);
extern void MoveGridCursorLeft_020bf218(void);
extern void ToggleSceneOption_020bf61c(void);
extern void UpdateSceneFrame_020bedb0(void);
extern void func_ov093_020bed38(void);
extern void func_ov093_020bf3d8(void);
extern void func_ov093_020bf5ac(void);
extern void func_ov093_020bf5e0(void);

void *data_ov093_020c3ff4[17] = {
    (void *)InitEntryGridScene_020beb20,
    (void *)func_ov093_020bed38,
    (void *)UpdateSceneFrame_020bedb0,
    (void *)0x00000005,
    (void *)0x0000D224,
    (void *)FinishGridPageScroll_020bee3c,
    (void *)FinishGridPageScrollDual_020bf028,
    (void *)MoveGridCursorLeft_020bf218,
    (void *)func_ov093_020bf3d8,
    NULL,
    (void *)func_ov093_020bf5ac,
    (void *)ToggleSceneOption_020bf61c,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)func_ov093_020bf5e0,
};

u32 data_ov093_020c3fb4[16] = {
    0x00000A6B, 0x0000012C, 0x00000A7C, 0x00000384,
    0x00000A8D, 0x00000384, 0x00000A9E, 0x00000258,
    0x00000AAF, 0x00000384, 0x00000AC0, 0x00000384,
    0x00000AD1, 0x00000708, 0x00000AE2, 0x00000258,
};
