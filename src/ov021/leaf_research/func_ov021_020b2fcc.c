#include "nitro/types.h"

extern u32 func_ov001_0209c3c0();
extern u32 func_ov021_020b0374();

/* Leaf script command: writes indexed table entry. */
u32 func_ov021_020b2fcc(u32 context, s32 operands)
{
    s32 indexOperand;
    s32 value1Operand;
    s32 value2Operand;
    s32 value3Operand;
    s32 table;

    indexOperand = func_ov021_020b0374();
    value1Operand = func_ov021_020b0374(context, operands + 8);
    value2Operand = func_ov021_020b0374(context, operands + 0x10);
    value3Operand = func_ov021_020b0374(context, operands + 0x18);
    table = func_ov001_0209c3c0();
    *(u32 *)(table + *(s32 *)(indexOperand + 4) * 0x20 + 0x18e8c) = *(u32 *)(value1Operand + 4);
    *(u32 *)(table + *(s32 *)(indexOperand + 4) * 0x20 + 0x18e90) = *(u32 *)(value2Operand + 4);
    *(u32 *)(table + *(s32 *)(indexOperand + 4) * 0x20 + 0x18e94) = *(u32 *)(value3Operand + 4);
    return 0;
}
