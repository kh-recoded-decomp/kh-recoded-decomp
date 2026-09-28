#include "nitro/types.h"

extern u32 func_ov001_020910c4();
extern u32 func_ov021_020b02b8();
extern u32 func_ov021_020b0374();
extern u32 func_ov021_020b03b0();
extern u32 func_ov021_020b03c8();

/* Leaf script command with vector and two operands. */
u32 func_ov021_020b364c(u32 context, s32 operands, u32 unusedArg, u32 extraArg)
{
    s32 actor;
    u32 yOperand;
    u32 zOperand;
    u8 vector[12];
    u32 stashedExtraArg;

    stashedExtraArg = extraArg;
    actor = func_ov021_020b0374();
    yOperand = func_ov021_020b0374(context, operands + 0x10);
    zOperand = func_ov021_020b0374(context, operands + 0x18);
    actor = func_ov021_020b02b8(context, *(u32 *)(actor + 4));
    if (actor != 0) {
        func_ov021_020b03c8(context, operands + 8, vector);
        yOperand = func_ov021_020b03b0(yOperand);
        zOperand = func_ov021_020b03b0(zOperand);
        func_ov001_020910c4(actor, vector, yOperand, zOperand);
    }
    return 0;
}
