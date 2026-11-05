#include "nitro/types.h"

extern u32 HandleSessionEffectEvent();
extern u32 ResolveTaggedValueRef();

/* Leaf script command triggers a sound effect. */
u32 StageScriptCmd_TriggerSessionEffectKind1(u32 context, s32 operands)
{
    s32 idOperand;

    idOperand = ResolveTaggedValueRef();
    ResolveTaggedValueRef(context, operands + 8);
    HandleSessionEffectEvent(1, *(u32 *)(idOperand + 4));
    return 0;
}
