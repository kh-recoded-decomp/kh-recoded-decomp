#include "nitro/types.h"

extern u32 func_ov021_020b0250();
extern u32 func_ov021_020b0374();

/* Leaf script command updates a step counter. */
u32 func_ov021_020b37a0(u32 context, s32 operands)
{
    s32 actor;
    s32 stepOperand;
    u32 step;

    actor = func_ov021_020b0374();
    stepOperand = func_ov021_020b0374(context, operands + 8);
    actor = func_ov021_020b0250(context, *(u32 *)(actor + 4));
    step = (*(s32 *)(stepOperand + 4) + 1U) & 0xffff;
    if (*(u8 *)(actor + 0x1b4) != step) {
        *(u8 *)(actor + 0x1b5) = 0;
    }
    *(char *)(actor + 0x1b4) = (char)step;
    return 0;
}
