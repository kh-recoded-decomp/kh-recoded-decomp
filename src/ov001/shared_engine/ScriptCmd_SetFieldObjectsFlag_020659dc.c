#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov001_0206e444(BOOL enabled);

int ScriptCmd_SetFieldObjectsFlag_020659dc(void *context, ScriptOperand *operands)
{
    int enabled;

    enabled = ScriptVm_ReadOperandInt_02025de4(context, operands);
    func_ov001_0206e444(enabled != 0);
    return 1;
}
