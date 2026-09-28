#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov001_0206e5a4(u32 value);

int ScriptCmd_SetFieldObjectManagerFlag_020655f8(void *context, ScriptOperand *operands)
{
    int enabled;

    enabled = ScriptVm_ReadOperandInt_02025de4(context, operands);
    func_ov001_0206e5a4(enabled != 0);
    return 1;
}
