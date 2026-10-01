#include "nitro/types.h"

typedef struct PaletteFlash {
    u8 pad_000[0xf4];
    u16 colors[6];
    u8 pad_100[4];
    u8 channelMask;
    u8 level;
    s8 step;
} PaletteFlash;

extern u16 func_ov001_0207a968(int from, int to, int level, int maxLevel);
extern int GFXi_EnqueueCommand_02014090(int command, int address, void *data, int size);

void PulsePaletteFlash_0207a9f4(PaletteFlash *flash)
{
    u16 color;
    int i;

    flash->level += flash->step;
    color = func_ov001_0207a968(0x1f, 0x7fff, flash->level, 0x1e);
    for (i = 0; i < 6; i++) {
        if (flash->channelMask & (1 << i)) {
            flash->colors[i] = color;
        }
    }
    GFXi_EnqueueCommand_02014090(0x1f, 0x1c2, flash->colors, 0xc);
    if (flash->level >= 0x1e) {
        flash->step = -1;
    } else if (flash->level == 0) {
        flash->step = 1;
    }
}
