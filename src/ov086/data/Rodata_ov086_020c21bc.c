#include "nitro/types.h"

extern void ClearPanelElement_020beb6c(void);
extern void DrawPanelElement_020beb28(void);

const u32 data_ov086_020c21ec[8] = {
    0x00000003, 0x0000000A, 0x00000010, 0x00000017,
    0x00000010, 0x00000010, 0x00000010, 0x0000000B,
};

const u32 data_ov086_020c21d0[7] = {
    0x00000004, 0x00000005, 0x00000006, 0x00000017,
    0x00000007, 0x00000008, 0x00000000,
};

void *const data_ov086_020c21bc[5] = {
    (void *)0x00000008,
    NULL,
    (void *)0x00000007,
    (void *)DrawPanelElement_020beb28,
    (void *)ClearPanelElement_020beb6c,
};
