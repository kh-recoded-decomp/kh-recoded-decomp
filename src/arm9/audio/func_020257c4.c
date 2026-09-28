#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x624];
    u8 pad_624[0x10];
    u32 source;
    u32 param;
    u32 handle;
} PcmChannel;

extern u32 func_0202a178(u32 source);

void func_020257c4(PcmChannel *ch, u32 source, u32 param)
{
    ch->source = source;
    ch->handle = func_0202a178(source);
    ch->param = param;
}
