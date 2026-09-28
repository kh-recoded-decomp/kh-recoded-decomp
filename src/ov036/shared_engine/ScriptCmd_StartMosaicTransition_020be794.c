#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov036_020bd800(int reveal, int duration);
extern void ScriptCmd_SetElemField_02025e18(void *context, u32 value);

int ScriptCmd_StartMosaicTransition_020be794(void *context, ScriptOperand *operands)
{
    int reveal = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int duration = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);

    func_ov036_020bd800(reveal, duration);
    ScriptCmd_SetElemField_02025e18(context, (u32)operands);
    return 0;
}
