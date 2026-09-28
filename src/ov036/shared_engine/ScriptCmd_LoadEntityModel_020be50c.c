#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern BOOL func_ov036_020bd1a0(int modelId, int depthSlot);
extern void func_02025438(u32 value);

BOOL ScriptCmd_LoadEntityModel_020be50c(void *context, ScriptOperand *operands)
{
    int modelId = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int depthSlot = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);

    if (func_ov036_020bd1a0(modelId, depthSlot)) {
        func_02025438(1);
        return TRUE;
    }
    return FALSE;
}
