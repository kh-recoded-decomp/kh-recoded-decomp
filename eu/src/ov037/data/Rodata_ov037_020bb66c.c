#include "src/overlays/ov037/ContinueMenu.h"

const u32 data_ov037_020bb690[8] = {
    0x00000004, 0x00000006, 0x00000009, 0x0000000B,
    0x0000000D, 0x0000000F, 0x00000011, 0x00000017,
};

const ContinueMenuListConfig gContinueMenuListConfig = {
    3, 1, 1, BlitContinueMenuWidget, ClearContinueMenuWidget,
};

const u16 data_ov037_020bb66c[8] = {
    9, 14, 14, 10, 1, 15, 0, 0,
};
