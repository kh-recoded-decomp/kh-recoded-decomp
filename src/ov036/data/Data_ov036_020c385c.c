#include "nitro/types.h"

extern void GXS_LoadBG0Char_02007940(void);
extern void GXS_LoadBG1Char_02007a20(void);
extern void GXS_LoadBG2Char_02007b00(void);
extern void GXS_LoadBG3Char_02007be0(void);
extern void GX_LoadBG0Char_020078d0(void);
extern void GX_LoadBG1Char_020079b0(void);
extern void GX_LoadBG2Char_02007a90(void);
extern void GX_LoadBG3Char_02007b70(void);

void (*data_ov036_020c385c[8])(void) = {
    GX_LoadBG0Char_020078d0,
    GX_LoadBG1Char_020079b0,
    GX_LoadBG2Char_02007a90,
    GX_LoadBG3Char_02007b70,
    GXS_LoadBG0Char_02007940,
    GXS_LoadBG1Char_02007a20,
    GXS_LoadBG2Char_02007b00,
    GXS_LoadBG3Char_02007be0,
};
