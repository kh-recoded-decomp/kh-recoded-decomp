#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x624];
    u32 fieldA;
    u32 fieldB;
    u32 fieldC;
    u32 enabled;
} PcmChannelInit;

BOOL func_020258f8(PcmChannelInit *ch)
{
    ch->fieldB = 0;
    ch->fieldC = 0;
    ch->fieldA = 0;
    ch->enabled = 1;
    return TRUE;
}
