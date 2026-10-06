#include "nitro/types.h"

extern u32 BeginWalkerMove();
extern u32 ResolveStageActorRef();
extern u32 ResolveTaggedValueRef();
extern u32 TaggedValueToFixed();
extern u32 ResolveVectorOperand();

/* Leaf script command with vector and two operands. */
u32 func_ov021_020b366c(u32 context, s32 operands, u32 unusedArg, u32 extraArg)
{
    s32 actor;
    u32 yOperand;
    u32 zOperand;
    u8 vector[12];
    u32 stashedExtraArg;

    stashedExtraArg = extraArg;
    actor = ResolveTaggedValueRef();
    yOperand = ResolveTaggedValueRef(context, operands + 0x10);
    zOperand = ResolveTaggedValueRef(context, operands + 0x18);
    actor = ResolveStageActorRef(context, *(u32 *)(actor + 4));
    if (actor != 0) {
        ResolveVectorOperand(context, operands + 8, vector);
        yOperand = TaggedValueToFixed(yOperand);
        zOperand = TaggedValueToFixed(zOperand);
        BeginWalkerMove(actor, vector, yOperand, zOperand);
    }
    return 0;
}
