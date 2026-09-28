#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *script, ScriptOperand *operand);
extern void *func_ov008_020a0b18(u16 objectId, int parameter);
extern void func_ov001_0207ee04(int slotIndex, void *object);

int ScriptCmd_CreateObjectWithParamInSlot_020a0630(void *script, ScriptOperand *operands)
{
    int slotIndex = ScriptVm_ReadOperandInt_02025de4(script, operands);
    int objectId = ScriptVm_ReadOperandInt_02025de4(script, operands + 1);
    int parameter = ScriptVm_ReadOperandInt_02025de4(script, operands + 2);

    func_ov001_0207ee04(slotIndex, func_ov008_020a0b18((u16)objectId, parameter));
    return 1;
}
