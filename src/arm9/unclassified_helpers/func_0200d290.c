#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    u32 flags;
} FlagsHolder;

BOOL func_0200d290(FlagsHolder *obj)
{
    return (obj->flags & 4) != 0;
}
