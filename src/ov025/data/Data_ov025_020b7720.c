#include "nitro/types.h"

extern void GXS_LoadBG2Scr_02007780(void);
extern void GXS_LoadBG3Scr_02007860(void);

void (*data_ov025_020b7720[2])(void) = {
    GXS_LoadBG2Scr_02007780,
    GXS_LoadBG3Scr_02007860,
};
