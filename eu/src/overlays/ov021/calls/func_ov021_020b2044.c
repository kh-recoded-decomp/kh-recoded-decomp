#include "nitro/types.h"

extern u32 ResolveTaggedValueRef();
extern u32 func_ov021_020b4ac4();

u32 func_ov021_020b2044(u32 self, int args)
{
    s32 resolved;

    resolved = ResolveTaggedValueRef();
    ResolveTaggedValueRef(self, args + 8);
    ResolveTaggedValueRef(self, args + 0x10);
    func_ov021_020b4ac4(self, *(u32 *)(resolved + 4));
    return 0;
}
