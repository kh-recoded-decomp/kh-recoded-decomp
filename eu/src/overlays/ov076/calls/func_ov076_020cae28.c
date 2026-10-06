#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x9c0c];
    s16 tileX;
    s16 tileY;
    u16 tileWidth;
    u16 tileHeight;
} MenuWork;

void func_ov076_020cae28(MenuWork *work, int *outTop, int *outLeft, int *outRight)
{
    int centerX = work->tileX + ((u32)work->tileWidth >> 1);

    *outLeft = (centerX - 7) * 8;
    *outTop = (work->tileY + work->tileHeight - 2) * 8;
    *outRight = (centerX + 7) * 8;
}
