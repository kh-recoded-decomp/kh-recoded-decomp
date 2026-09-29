#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *script, ScriptOperand *operand);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern void func_ov040_020be02c(u32 entry, int *first, int *second);

int ScriptCmd_ApplyOperandPair_020a0844(void *script, ScriptOperand *operands)
{
    int first = ScriptVm_ReadOperandInt_02025de4(script, operands);
    int second = ScriptVm_ReadOperandInt_02025de4(script, operands + 1);

    func_ov040_020be02c(GetBoundedEntryField_0206db5c(0), &first, &second);
    return 1;
}
