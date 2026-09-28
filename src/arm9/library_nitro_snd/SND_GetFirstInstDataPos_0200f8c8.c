#include "nitro/types.h"

typedef struct SNDInstPos {
    u32 prgNo;
    u32 index;
} SNDInstPos;

typedef struct SNDBankData SNDBankData;

SNDInstPos SND_GetFirstInstDataPos_0200f8c8(const SNDBankData *bank)
{
    SNDInstPos pos;

    pos.prgNo = 0;
    pos.index = 0;
    return pos;
}
