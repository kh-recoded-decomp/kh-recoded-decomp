#include "nitro/types.h"

extern void DestroyFndObjectList(u32 context);

void func_ov001_0206f720(u32 context)
{
    DestroyFndObjectList(context + 0x51c);
}
