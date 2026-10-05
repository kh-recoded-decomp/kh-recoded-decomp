#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitPageMenu_020c4260(void);
extern void SelectNextPage_020c4e80(void);
extern void ShutdownPageMenu_020c4354(void);
extern void StepCursorBack_020c4f40(void);
extern void StepCursorForward_020c4f68(void);
extern void _fp_init_020c4350(void);
extern void func_ov078_020c4dd8(void);
extern void func_ov078_020c4f24(void);

u32 data_ov078_020c5004[64] = {
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

void *data_ov078_020c4fc0[17] = {
    (void *)InitPageMenu_020c4260,
    (void *)ShutdownPageMenu_020c4354,
    (void *)_fp_init_020c4350,
    NULL,
    (void *)0x000005D8,
    (void *)func_ov078_020c4dd8,
    (void *)SelectNextPage_020c4e80,
    NULL,
    NULL,
    NULL,
    (void *)func_ov078_020c4f24,
    NULL,
    NULL,
    (void *)StepCursorBack_020c4f40,
    (void *)StepCursorForward_020c4f68,
    NULL,
    (void *)func_ov078_020c4f24,
};
