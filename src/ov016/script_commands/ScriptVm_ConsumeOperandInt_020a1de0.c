#include "nitro/types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

extern s32 ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);

s32 ScriptVm_ConsumeOperandInt_020a1de0(void *vm, ScriptOperand **cursor)
{
    ScriptOperand *operand = *cursor;

    *cursor = operand + 1;
    return ScriptVm_ReadOperandInt_02025de4(vm, operand);
}
