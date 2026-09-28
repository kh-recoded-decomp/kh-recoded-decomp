#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x64];
    u8 channel[0x48];
    u8 *fileOffset;
    u8 info[0x40];
} Player;

extern void func_0200b648(void *channel, void *pos, u32 zero);
extern void func_0200b674(void *channel, u32 value2, u32 value3);

void func_0202178c(Player *player, u32 value2, u32 value3, u32 offset)
{
    func_0200b648(&player->channel, player->fileOffset + offset, 0);
    func_0200b674(&player->channel, value2, value3);
}
