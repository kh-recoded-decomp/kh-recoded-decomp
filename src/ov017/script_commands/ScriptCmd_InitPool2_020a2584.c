#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4204(void);
extern void InitPool2_020a4158(void *manager, s32 capacity);

int ScriptCmd_InitPool2_020a2584(void *vm, ScriptOperand *operands)
{
    int capacity = ScriptVm_ReadOperandInt_02025de4(vm, operands);

    InitPool2_020a4158(func_ov017_020a4204(), (u16)capacity);
    return 1;
}
