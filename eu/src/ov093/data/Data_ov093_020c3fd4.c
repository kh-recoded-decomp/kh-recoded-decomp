#include "nitro/types.h"

#pragma explicit_zero_data on

extern void FinishGridPageScroll(void);
extern void FinishGridPageScrollDual(void);
extern void InitEntryGridScene(void);
extern void MoveGridCursorLeft(void);
extern void ToggleSceneOption(void);
extern void UpdateSceneFrame(void);
extern void func_ov093_020bed58(void);
extern void func_ov093_020bf3f8(void);
extern void func_ov093_020bf5cc(void);
extern void func_ov093_020bf600(void);

void *data_ov093_020c4014[17] = {
    (void *)InitEntryGridScene,
    (void *)func_ov093_020bed58,
    (void *)UpdateSceneFrame,
    (void *)0x00000005,
    (void *)0x0000D224,
    (void *)FinishGridPageScroll,
    (void *)FinishGridPageScrollDual,
    (void *)MoveGridCursorLeft,
    (void *)func_ov093_020bf3f8,
    NULL,
    (void *)func_ov093_020bf5cc,
    (void *)ToggleSceneOption,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)func_ov093_020bf600,
};

u32 data_ov093_020c3fd4[16] = {
    0x00000A6B, 0x0000012C, 0x00000A7C, 0x00000384,
    0x00000A8D, 0x00000384, 0x00000A9E, 0x00000258,
    0x00000AAF, 0x00000384, 0x00000AC0, 0x00000384,
    0x00000AD1, 0x00000708, 0x00000AE2, 0x00000258,
};
