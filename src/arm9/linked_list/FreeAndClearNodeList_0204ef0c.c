#include "nitro/types.h"

extern void func_0204eee0(u32 *node);

void FreeAndClearNodeList_0204ef0c(int manager)
{
    u32 *node = *(u32 **)(manager + 0x4618);
    while (node != 0) {
        u32 *next = (u32 *)node[0x18];
        func_0204eee0(node + 1);
        *node = 0;
        node = next;
    }
    *(u16 *)(manager + 0x4612) = 0;
}
