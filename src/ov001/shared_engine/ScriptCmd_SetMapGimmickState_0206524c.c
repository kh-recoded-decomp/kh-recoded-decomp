#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov001_02067b1c(int gimmickId, int secondaryState, int primaryState);

int ScriptCmd_SetMapGimmickState_0206524c(void *context, ScriptOperand *operands)
{
    int gimmickId;
    int primaryState;
    int secondaryState;

    gimmickId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    primaryState = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    secondaryState = ScriptVm_ReadOperandInt_02025de4(context, operands + 2);
    func_ov001_02067b1c(gimmickId, secondaryState, primaryState);
    return 1;
}
