#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitializeOverlay088(void);
extern void ShutdownOverlay088(void);
extern void func_ov088_020bee58(void);

u32 data_ov088_020beec0[18] = {
    0x00000006, 0x00000007, 0x00000008, 0x00000009,
    0x0000000A, 0x0000000B, 0x0000000C, 0x0000000D,
    0x0000000E, 0x0000000F, 0x00000010, 0x00000011,
    0x00000012, 0x00000013, 0x00000014, 0x00000015,
    0x00000016, 0x00000017,
};

void *data_ov088_020bee80[16] = {
    (void *)InitializeOverlay088,
    (void *)ShutdownOverlay088,
    (void *)func_ov088_020bee58,
    (void *)0x00000040,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
