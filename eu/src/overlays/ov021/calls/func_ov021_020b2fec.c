#include "nitro/types.h"

extern u32 func_ov001_0209c3e8();
extern u32 ResolveTaggedValueRef();

/* Leaf script command: writes indexed table entry. */
u32 func_ov021_020b2fec(u32 context, s32 operands)
{
    s32 indexOperand;
    s32 value1Operand;
    s32 value2Operand;
    s32 value3Operand;
    s32 table;

    indexOperand = ResolveTaggedValueRef();
    value1Operand = ResolveTaggedValueRef(context, operands + 8);
    value2Operand = ResolveTaggedValueRef(context, operands + 0x10);
    value3Operand = ResolveTaggedValueRef(context, operands + 0x18);
    table = func_ov001_0209c3e8();
    *(u32 *)(table + *(s32 *)(indexOperand + 4) * 0x20 + 0x18e8c) = *(u32 *)(value1Operand + 4);
    *(u32 *)(table + *(s32 *)(indexOperand + 4) * 0x20 + 0x18e90) = *(u32 *)(value2Operand + 4);
    *(u32 *)(table + *(s32 *)(indexOperand + 4) * 0x20 + 0x18e94) = *(u32 *)(value3Operand + 4);
    return 0;
}
