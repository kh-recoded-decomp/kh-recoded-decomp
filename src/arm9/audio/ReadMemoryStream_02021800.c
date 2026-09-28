#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x64];
    u8 channel[0x48];
    u8 *fileOffset;
    u8 info[0x40];
} Player;

extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);

u32 ReadMemoryStream_02021800(Player *player, void *dest, u32 size, u32 offset)
{
    MI_CpuCopy8_01ff89a8(player->fileOffset + offset, dest, size);
    return size;
}
