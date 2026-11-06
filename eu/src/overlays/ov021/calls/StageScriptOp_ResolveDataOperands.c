#include "nitro/types.h"

extern u32 ResolveTaggedValueRef();
extern u32 ResolveStageScriptCommandDataOffset();

u32 StageScriptOp_ResolveDataOperands(u32 self, int args)
{
    s32 resolved;

    resolved = ResolveTaggedValueRef();
    ResolveTaggedValueRef(self, args + 8);
    ResolveTaggedValueRef(self, args + 0x10);
    ResolveStageScriptCommandDataOffset(self, *(u32 *)(resolved + 4));
    return 0;
}
