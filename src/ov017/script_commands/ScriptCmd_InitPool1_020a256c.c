#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4204(void);
extern void InitPool1_020a4138(void *manager, s32 capacity);

int ScriptCmd_InitPool1_020a256c(void *vm, ScriptOperand *operands)
{
    int capacity = ScriptVm_ReadOperandInt_02025de4(vm, operands);

    InitPool1_020a4138(func_ov017_020a4204(), (u16)capacity);
    return 1;
}
