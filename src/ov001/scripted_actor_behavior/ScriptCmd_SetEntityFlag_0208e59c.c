#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov001_0206e65c(int entityIndex, BOOL enabled);

int ScriptCmd_SetEntityFlag_0208e59c(void *context, ScriptOperand *operands)
{
    int entityIndex;
    int enabled;

    entityIndex = ScriptVm_ReadOperandInt_02025de4(context, operands);
    enabled = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    func_ov001_0206e65c(entityIndex, enabled != 0);
    return 1;
}
