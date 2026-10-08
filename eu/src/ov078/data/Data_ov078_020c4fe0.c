#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitPageMenu(void);
extern void SelectNextPage(void);
extern void StepCursorBack(void);
extern void StepCursorForward(void);
extern void func_ov078_020c4370(void);
extern void ShutdownPageMenu(void);
extern void func_ov078_020c4df8(void);
extern void func_ov078_020c4f44(void);

u32 data_ov078_020c5024[64] = {
    0xFFFFFFFF, 0x0000000A, 0x00000000, 0x00000016,
    0x00000002, 0x000000AE, 0x00000002, 0x00000002,
    0x00000021, 0xFFFFFFFF, 0x00000007, 0x00000003,
    0x00000012, 0x00000002, 0x00000048, 0x00000004,
    0x00000002, 0x00000011, 0xFFFFFFFF, 0x00000008,
    0x00000006, 0x0000000E, 0x00000002, 0x00000000,
    0x00000003, 0x00000002, 0x00000009, 0xFFFFFFFF,
    0x00000008, 0x00000008, 0x0000000E, 0x00000002,
    0x00000000, 0x00000003, 0x00000002, 0x00000009,
    0xFFFFFFFF, 0x00000008, 0x0000000A, 0x0000000E,
    0x00000002, 0x00000000, 0x00000003, 0x00000002,
    0x00000009, 0xFFFFFFFF, 0x00000006, 0x0000000E,
    0x00000006, 0x00000002, 0x00000018, 0x00000003,
    0x00000002, 0x00000011, 0xFFFFFFFF, 0x00000006,
    0x00000010, 0x00000006, 0x00000002, 0x00000018,
    0x00000003, 0x00000002, 0x00000011, 0xFFFFFFFF,
};

void *data_ov078_020c4fe0[17] = {
    (void *)InitPageMenu,
    (void *)ShutdownPageMenu,
    (void *)func_ov078_020c4370,
    NULL,
    (void *)0x000005D8,
    (void *)func_ov078_020c4df8,
    (void *)SelectNextPage,
    NULL,
    NULL,
    NULL,
    (void *)func_ov078_020c4f44,
    NULL,
    NULL,
    (void *)StepCursorBack,
    (void *)StepCursorForward,
    NULL,
    (void *)func_ov078_020c4f44,
};
