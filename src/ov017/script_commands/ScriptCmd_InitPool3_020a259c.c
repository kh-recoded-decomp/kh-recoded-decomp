#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4204(void);
extern void InitPool3_020a4178(void *manager, s32 capacity);

int ScriptCmd_InitPool3_020a259c(void *vm, ScriptOperand *operands)
{
    int capacity = ScriptVm_ReadOperandInt_02025de4(vm, operands);

    InitPool3_020a4178(func_ov017_020a4204(), (u16)capacity);
    return 1;
}
