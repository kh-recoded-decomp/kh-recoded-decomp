#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    int pulseFrame;
} PulseMenu;

extern u16 gGroupMenuGaugeGlobalsStorage;
extern int gGroupSceneGlobals[];
extern int NNS_GfdRegisterNewVramTransferTask(void *a, int b, int c, int d);

void PulseMenuHighlightColor(PulseMenu *menu)
{
    int frame = menu->pulseFrame;
    s16 level;
    s16 blue;

    if (frame > 30) {
        frame = 60 - frame;
    }
    level = frame * 31 / 30;
    blue = frame * 16 / 30;
    gGroupMenuGaugeGlobalsStorage = (blue << 10) | ((level << 5) | level);
    menu->pulseFrame = (menu->pulseFrame + 1) % 60;
    NNS_GfdRegisterNewVramTransferTask((void *)0xf, 0x18e, (int)&gGroupSceneGlobals[2], 2);
}
