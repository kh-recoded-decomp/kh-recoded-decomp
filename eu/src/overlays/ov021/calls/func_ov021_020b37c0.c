#include "nitro/types.h"

extern u32 ResolveEventRecordRef();
extern u32 ResolveTaggedValueRef();

/* Leaf script command updates a step counter. */
u32 func_ov021_020b37c0(u32 context, s32 operands)
{
    s32 actor;
    s32 stepOperand;
    u32 step;

    actor = ResolveTaggedValueRef();
    stepOperand = ResolveTaggedValueRef(context, operands + 8);
    actor = ResolveEventRecordRef(context, *(u32 *)(actor + 4));
    step = (*(s32 *)(stepOperand + 4) + 1U) & 0xffff;
    if (*(u8 *)(actor + 0x1b4) != step) {
        *(u8 *)(actor + 0x1b5) = 0;
    }
    *(char *)(actor + 0x1b4) = (char)step;
    return 0;
}
