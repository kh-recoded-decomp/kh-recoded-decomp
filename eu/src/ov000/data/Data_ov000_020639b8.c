#include "nitro/types.h"

#pragma explicit_zero_data on

extern void EnterOv039Selection(void);
extern void ExitOv039Selection(void);

u32 gOv039SelectionResultMap[13] = {
    0x00000000, 0x0000000E, 0x00000003, 0x00000004,
    0x00000005, 0x00000006, 0x00000007, 0x0000000F,
    0x0000000C, 0x00000010, 0x0000000D, 0x00000000,
    0x00000000,
};

void *gOv039SelectionDescriptor[5] = {
    (void *)0x000E0008,
    (void *)EnterOv039Selection,
    (void *)ExitOv039Selection,
    (void *)0x00000008,
    NULL,
};
