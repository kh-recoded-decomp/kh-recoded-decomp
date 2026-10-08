#include "nitro/types.h"

#pragma explicit_zero_data on

extern void TeardownCurrentHeap(void);
extern void InitTitleScreen(void);

void *data_ov000_02063870[5] = {
    (void *)0x00110008,
    (void *)InitTitleScreen,
    (void *)TeardownCurrentHeap,
    (void *)0x000066EC,
    NULL,
};

u32 data_ov000_02063860[4] = {
    0x00000007, 0x00000008, 0x00000009, 0x0000000A,
};
