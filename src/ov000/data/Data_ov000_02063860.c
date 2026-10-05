#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitTitleScreen_02063240(void);
extern void TeardownCurrentHeap_020633d8(void);

void *data_ov000_02063870[5] = {
    (void *)0x00110008,
    (void *)InitTitleScreen_02063240,
    (void *)TeardownCurrentHeap_020633d8,
    (void *)0x000066EC,
    NULL,
};

u32 data_ov000_02063860[4] = {
    0x00000007, 0x00000008, 0x00000009, 0x0000000A,
};
