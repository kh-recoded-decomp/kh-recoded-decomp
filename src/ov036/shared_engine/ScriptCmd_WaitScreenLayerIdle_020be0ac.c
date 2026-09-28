#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern BOOL func_ov036_020bd540(int screen);

BOOL ScriptCmd_WaitScreenLayerIdle_020be0ac(void *context, ScriptOperand *operands)
{
    if (!func_ov036_020bd540(ScriptVm_ReadOperandInt_02025de4(context, operands))) {
        return TRUE;
    }
    return FALSE;
}
