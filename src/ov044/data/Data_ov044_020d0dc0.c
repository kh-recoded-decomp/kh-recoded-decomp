#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitPanelMotionA_020d0020(void);
extern void InitPanelMotionB_020d0050(void);
extern void InitPanelSwayA_020cffa0(void);
extern void InitPanelSwayB_020cff60(void);
extern void func_ov044_020cffe0(void);
extern void func_ov044_020d0000(void);

u32 data_ov044_020d0df0[36] = {
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

void *data_ov044_020d0dc4[11] = {
    (void *)0x0000A000,
    (void *)0x00000333,
    (void *)0x0000A000,
    (void *)0x000004CD,
    (void *)0x00014000,
    (void *)InitPanelSwayB_020cff60,
    (void *)InitPanelSwayA_020cffa0,
    (void *)func_ov044_020cffe0,
    (void *)func_ov044_020d0000,
    (void *)InitPanelMotionA_020d0020,
    (void *)InitPanelMotionB_020d0050,
};

u32 data_ov044_020d0dc0[1] = {
    0x0000019A,
};
