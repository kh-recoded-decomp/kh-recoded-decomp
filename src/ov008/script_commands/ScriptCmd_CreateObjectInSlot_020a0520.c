#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *script, ScriptOperand *operand);
extern void *func_ov008_020a1108(u16 objectId);
extern void func_ov001_0207ee04(int slotIndex, void *object);

int ScriptCmd_CreateObjectInSlot_020a0520(void *script, ScriptOperand *operands)
{
    int slotIndex = ScriptVm_ReadOperandInt_02025de4(script, operands);
    int objectId = ScriptVm_ReadOperandInt_02025de4(script, operands + 1);

    func_ov001_0207ee04(slotIndex, func_ov008_020a1108((u16)objectId));
    return 1;
}
