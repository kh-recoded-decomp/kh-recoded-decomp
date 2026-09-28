#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0A[6];
    u32 sub;
} Container;

extern s32 func_0202fdb0(u32 *sub);

void func_020366f8(Container *obj)
{
    if (func_0202fdb0(&obj->sub) != 0) {
        obj->flags = obj->flags | 0x41;
    }
}
