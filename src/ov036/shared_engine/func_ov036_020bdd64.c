#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov036_020bcec8(int entryId, int direction, int duration);

int func_ov036_020bdd64(void *context, ScriptOperand *operands)
{
    int entryId = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int direction = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
    int duration = ScriptVm_ReadOperandInt_02025de4(context, &operands[2]);

    func_ov036_020bcec8(entryId, direction, duration);
    return 0;
}
