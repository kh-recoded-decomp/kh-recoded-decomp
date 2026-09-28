#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 flags;
} StatusBlock_02056fe0;

extern StatusBlock_02056fe0 data_02056fe0;

BOOL func_020092a0(void)
{
    if ((data_02056fe0.flags & 4) == 0) {
        return TRUE;
    }
    return FALSE;
}
