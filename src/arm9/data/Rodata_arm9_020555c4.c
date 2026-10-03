#include "nitro/types.h"

extern void Bg_SetMainBg2AffineControl_0202b03c(void);
extern void Bg_SetMainBg3AffineControl_0202b078(void);
extern void Bg_SetSubBg2AffineControl_0202b21c(void);
extern void Bg_SetSubBg3AffineControl_0202b258(void);

void (*const data_020555c4[8])(void) = {
    NULL,
    NULL,
    Bg_SetMainBg2AffineControl_0202b03c,
    Bg_SetMainBg3AffineControl_0202b078,
    NULL,
    NULL,
    Bg_SetSubBg2AffineControl_0202b21c,
    Bg_SetSubBg3AffineControl_0202b258,
};
