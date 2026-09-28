#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4204(void);
extern void func_ov017_020a422c(void *manager, u32 value);

int ScriptCmd_SetManagerValue_020a2628(void *vm, ScriptOperand *operands)
{
    int value = ScriptVm_ReadOperandInt_02025de4(vm, operands);

    func_ov017_020a422c(func_ov017_020a4204(), value);
    return 1;
}
