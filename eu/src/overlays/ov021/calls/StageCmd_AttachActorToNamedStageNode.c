#include "nitro/types.h"

extern u32 GetLargeRecordIndex();
extern u32 AttachActorToStageNode();
extern u32 ResolveStageActorRef();
extern u32 ResolveTaggedValueRef();
extern u32 ResolveStageScriptCommandDataOffset();

u32 StageCmd_AttachActorToNamedStageNode(u32 self, int args)
{
    s32 resolvedA;
    s32 resolvedB;
    s32 resolvedC;
    u32 factor;
    u32 value;

    resolvedA = ResolveTaggedValueRef();
    resolvedB = ResolveTaggedValueRef(self, args + 8);
    resolvedC = ResolveTaggedValueRef(self, args + 0x10);
    resolvedA = ResolveStageActorRef(self, *(u32 *)(resolvedA + 4));
    resolvedB = ResolveStageActorRef(self, *(u32 *)(resolvedB + 4));
    if (resolvedA == 0) {
        return 0;
    }
    if (resolvedB == 0) {
        return 0;
    }
    factor = GetLargeRecordIndex();
    value = ResolveStageScriptCommandDataOffset(self, *(u32 *)(resolvedC + 4));
    AttachActorToStageNode(resolvedA, factor, value, 0);
    return 0;
}
