#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0A[6];
    u32 sub;
} Container;

extern void func_020353a4(u32 *sub);

void func_020359b0(Container *obj)
{
    if ((obj->flags & 4) != 0) {
        func_020353a4(&obj->sub);
        obj->flags = obj->flags & 0xfffb;
    }
}
