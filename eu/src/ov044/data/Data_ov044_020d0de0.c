#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitPanelMotionA(void);
extern void InitPanelMotionB(void);
extern void InitPanelSwayA(void);
extern void InitPanelSwayB(void);
extern void func_ov044_020d0000(void);
extern void func_ov044_020d0020(void);

u32 data_ov044_020d0e10[36] = {
    0x00000000, 0x00000000, 0xFFFED000, 0x0005A000,
    0x00022512, 0x00000000, 0x00000000, 0x00000000,
    0xFFFDF000, 0x0005A000, 0x00022512, 0x00000000,
    0x00000000, 0x0000019A, 0xFFFEA9A2, 0x0005A000,
    0x00022512, 0x00000000, 0x00000000, 0xFFFFE801,
    0xFFFDFCD6, 0x0005A000, 0x00022512, 0x00000000,
    0x00000000, 0x00004000, 0xFFFEB33C, 0x0005A000,
    0x00022512, 0x00000000, 0x00000000, 0x00002000,
    0xFFFDFCD6, 0x0005A000, 0x00022512, 0x00000000,
};

void *data_ov044_020d0de4[11] = {
    (void *)0x0000A000,
    (void *)0x00000333,
    (void *)0x0000A000,
    (void *)0x000004CD,
    (void *)0x00014000,
    (void *)InitPanelSwayB,
    (void *)InitPanelSwayA,
    (void *)func_ov044_020d0000,
    (void *)func_ov044_020d0020,
    (void *)InitPanelMotionA,
    (void *)InitPanelMotionB,
};

u32 data_ov044_020d0de0[1] = {
    0x0000019A,
};
