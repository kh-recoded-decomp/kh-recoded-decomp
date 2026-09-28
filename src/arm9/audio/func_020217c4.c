#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x64];
    u8 channel[0x48];
    u8 *fileOffset;
    u8 info[0x40];
} Player;

extern void func_0200b3c0(void *channel);

void func_020217c4(Player *player)
{
    func_0200b3c0(&player->channel);
}
