#include "nitro/types.h"

extern void GX_LoadBG0Char_020078d0(void);
extern void GX_LoadBG1Char_020079b0(void);
extern void GX_LoadBG2Char_02007a90(void);
extern void GX_LoadBG3Char_02007b70(void);

void (*const data_ov081_020c5c64[4])(void) = {
    GX_LoadBG0Char_020078d0,
    GX_LoadBG1Char_020079b0,
    GX_LoadBG2Char_02007a90,
    GX_LoadBG3Char_02007b70,
};
