#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x64];
    u8 channel[0x48];
    u8 *fileOffset;
    u8 info[0x40];
} Player;

extern u8 *func_0201ee28(u32 fileId);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);

BOOL OpenMemoryStream_020217d4(Player *player, u32 fileId)
{
    player->fileOffset = func_0201ee28(fileId);
    MI_CpuCopy8_01ff89a8(player->fileOffset, player->info, 0x40);
    return TRUE;
}
