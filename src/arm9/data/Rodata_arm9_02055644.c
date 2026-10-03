#include "nitro/types.h"

extern void Bg_SetMainBg2ExtControl_0202b0b4(void);
extern void Bg_SetMainBg3ExtControl_0202b0f0(void);
extern void Bg_SetSubBg2ExtControl_0202b294(void);
extern void Bg_SetSubBg3ExtControl_0202b2d0(void);

void (*const data_02055644[8])(void) = {
    NULL,
    NULL,
    Bg_SetMainBg2ExtControl_0202b0b4,
    Bg_SetMainBg3ExtControl_0202b0f0,
    NULL,
    NULL,
    Bg_SetSubBg2ExtControl_0202b294,
    Bg_SetSubBg3ExtControl_0202b2d0,
};
