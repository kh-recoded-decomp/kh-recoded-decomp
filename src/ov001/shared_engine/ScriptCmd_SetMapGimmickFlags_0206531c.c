#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov001_02067bec(int gimmickId, u16 flags, int stateA, int stateB, BOOL refresh);

int ScriptCmd_SetMapGimmickFlags_0206531c(void *context, ScriptOperand *operands)
{
    int gimmickId;
    u32 flags;
    int refresh;

    gimmickId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    flags = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    refresh = ScriptVm_ReadOperandInt_02025de4(context, operands + 2);
    func_ov001_02067bec(gimmickId, flags, -1, -1, refresh);
    return 1;
}
