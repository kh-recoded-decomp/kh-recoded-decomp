#include "nitro/types.h"

extern void func_ov015_02078df0(u8 *dst, u8 *src);
extern int GFXi_EnqueueCommand_02014090(u32 command, u32 offset, void *data, u32 size);

void ConvertTileGrid_02078d14(u8 *dst, u8 *src, u32 command, int tileOffset)
{
    int row;
    int col;
    int srcOffset;

    for (row = 0; row < 18; row++) {
        srcOffset = row * 0x480;
        for (col = 0; col < 18; col++) {
            func_ov015_02078df0(dst + (row * 0x480 + col * 0x40), src + srcOffset);
            srcOffset += 8;
        }
    }
    GFXi_EnqueueCommand_02014090(command, tileOffset << 6, dst, 0x5100);
}
