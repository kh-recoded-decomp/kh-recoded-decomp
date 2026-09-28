#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov001_02068790(u16 first, u16 second);

int ScriptCmd_QueueEventPair_02065224(void *context, ScriptOperand *operands)
{
    u32 first;
    u32 second;

    first = ScriptVm_ReadOperandInt_02025de4(context, operands);
    second = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    func_ov001_02068790(first, second);
    return 1;
}
