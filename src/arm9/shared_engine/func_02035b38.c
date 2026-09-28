#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
} Container;

BOOL func_02035b38(Container *obj)
{
    return (obj->flags & 2) != 0;
}
