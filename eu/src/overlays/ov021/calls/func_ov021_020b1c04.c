#include "nitro/types.h"

extern u32 FindActorResourceIndexByName();
extern u32 GetNodePosition();
extern u32 ResolveStageActorRef();
extern u32 ResolveTaggedValueRef();
extern u32 TaggedValueToInt();
extern u32 func_ov021_020b4ac4();

u32 func_ov021_020b1c04(int self, int args)
{
    s32 resolved;
    u32 value;
    s32 target;

    resolved = ResolveTaggedValueRef(self, args + 8);
    ResolveTaggedValueRef(self, args + 0x10);
    value = TaggedValueToInt();
    target = ResolveStageActorRef(self, value);
    if (target == 0) {
        return 0;
    }
    value = func_ov021_020b4ac4(self, *(u32 *)(resolved + 4));
    value = FindActorResourceIndexByName(target, value);
    GetNodePosition(target, value, self + 0x34);
    return 0;
}
