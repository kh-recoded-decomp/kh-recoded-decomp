#include "nitro/types.h"

extern u8 data_02055afc[];

u8 *GetPageTableEntry_02052124(u32 index)
{
    if (index > 5) {
        return NULL;
    }
    return data_02055afc + index * 0x1a;
}
