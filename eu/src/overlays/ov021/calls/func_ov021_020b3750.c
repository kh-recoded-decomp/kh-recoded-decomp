#include "nitro/types.h"

extern u32 PlayActorAnimationSlot();
extern u32 ResolveStageActorRef();
extern u32 ResolveTaggedValueRef();

/* Leaf script command with four operands. */
u32 func_ov021_020b3750(u32 context, s32 operands)
{
    s32 actor;
    s32 operand1;
    s32 operand2;
    s32 operand3;
    s32 operand4;

    actor = ResolveTaggedValueRef();
    operand1 = ResolveTaggedValueRef(context, operands + 8);
    operand2 = ResolveTaggedValueRef(context, operands + 0x10);
    operand3 = ResolveTaggedValueRef(context, operands + 0x18);
    operand4 = ResolveTaggedValueRef(context, operands + 0x20);
    actor = ResolveStageActorRef(context, *(u32 *)(actor + 4));
    if (actor == 0) {
        return 0;
    }
    PlayActorAnimationSlot(actor, *(u32 *)(operand1 + 4) & 0xffff, (s32)(s16)*(u32 *)(operand2 + 4),
                         *(u32 *)(operand3 + 4), *(u32 *)(operand4 + 4));
    return 0;
}
