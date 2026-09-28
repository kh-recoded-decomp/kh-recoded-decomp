#include "nitro/types.h"

extern u32 func_ov001_02091a00();
extern u32 func_ov021_020b02b8();
extern u32 func_ov021_020b0374();

/* Leaf script command with four operands. */
u32 func_ov021_020b3730(u32 context, s32 operands)
{
    s32 actor;
    s32 operand1;
    s32 operand2;
    s32 operand3;
    s32 operand4;

    actor = func_ov021_020b0374();
    operand1 = func_ov021_020b0374(context, operands + 8);
    operand2 = func_ov021_020b0374(context, operands + 0x10);
    operand3 = func_ov021_020b0374(context, operands + 0x18);
    operand4 = func_ov021_020b0374(context, operands + 0x20);
    actor = func_ov021_020b02b8(context, *(u32 *)(actor + 4));
    if (actor == 0) {
        return 0;
    }
    func_ov001_02091a00(actor, *(u32 *)(operand1 + 4) & 0xffff, (s32)(s16)*(u32 *)(operand2 + 4),
                         *(u32 *)(operand3 + 4), *(u32 *)(operand4 + 4));
    return 0;
}
