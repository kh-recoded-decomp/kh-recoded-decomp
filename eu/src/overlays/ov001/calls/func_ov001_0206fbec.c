#include "nitro/types.h"

extern void DestroyTaskObjectWrapper();

void func_ov001_0206fbec(u32 context)
{
    DestroyTaskObjectWrapper(*(u32 *)(context + 0x418));
    DestroyTaskObjectWrapper(*(u32 *)(context + 0x414));
    DestroyTaskObjectWrapper(*(u32 *)(context + 0x41c));
    DestroyTaskObjectWrapper(*(u32 *)(context + 0x420));
    DestroyTaskObjectWrapper(*(u32 *)(context + 0x424));
    DestroyTaskObjectWrapper(*(u32 *)(context + 0x428));
    if (*(s32 *)(context + 0x430) != 0) {
        DestroyTaskObjectWrapper();
    }
    if (*(s32 *)(context + 0x434) != 0) {
        DestroyTaskObjectWrapper();
    }
    DestroyTaskObjectWrapper(*(u32 *)(context + 0x438));
}
