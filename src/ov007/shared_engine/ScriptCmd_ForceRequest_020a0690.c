#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *script, ScriptOperand *operand);
extern void func_ov035_020bae84(int requestId, int mode, BOOL force);

int ScriptCmd_ForceRequest_020a0690(void *script, ScriptOperand *operands)
{
    int requestId = ScriptVm_ReadOperandInt_02025de4(script, operands);
    int mode = ScriptVm_ReadOperandInt_02025de4(script, operands + 1);

    func_ov035_020bae84(requestId, mode, TRUE);
    return 1;
}
