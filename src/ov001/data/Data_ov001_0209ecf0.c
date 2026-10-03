#include "nitro/types.h"

extern void GXS_LoadBG0Scr_020075c0(void);
extern void GXS_LoadBG1Scr_020076a0(void);
extern void GXS_LoadBG2Scr_02007780(void);
extern void GXS_LoadBG3Scr_02007860(void);
extern void GX_LoadBG1Scr_02007630(void);
extern void GX_LoadBG2Scr_02007710(void);
extern void GX_LoadBG3Scr_020077f0(void);

void (*data_ov001_0209ecf0[7])(void) = {
    GX_LoadBG1Scr_02007630,
    GX_LoadBG2Scr_02007710,
    GX_LoadBG3Scr_020077f0,
    GXS_LoadBG0Scr_020075c0,
    GXS_LoadBG1Scr_020076a0,
    GXS_LoadBG2Scr_02007780,
    GXS_LoadBG3Scr_02007860,
};
