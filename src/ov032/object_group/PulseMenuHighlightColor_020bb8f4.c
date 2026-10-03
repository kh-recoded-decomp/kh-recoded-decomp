#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    int pulseFrame;
} PulseMenu;

extern u16 highlightColor_020c0068;
extern int contextData_020c0068[];
extern int GFXi_EnqueueCommand_02014090(void *a, int b, int c, int d);

void PulseMenuHighlightColor_020bb8f4(PulseMenu *menu)
{
    int frame = menu->pulseFrame;
    s16 level;
    s16 blue;

    if (frame > 30) {
        frame = 60 - frame;
    }
    level = frame * 31 / 30;
    blue = frame * 16 / 30;
    highlightColor_020c0068 = (blue << 10) | ((level << 5) | level);
    menu->pulseFrame = (menu->pulseFrame + 1) % 60;
    GFXi_EnqueueCommand_02014090((void *)0xf, 0x18e, (int)contextData_020c0068, 2);
}
