#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f028(int index);
extern void *FieldObject_CreateAtPosition_020a0b7c(void *objectClass, int slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, int hidden);

int ScriptCmd_CreateObjectAtPosition_020a054c(void *vm, ScriptOperand *operands)
{
    int classIndex;
    int slotIndex;
    u32 saveBits;
    VecFx32 position;
    int hidden;

    classIndex = ScriptVm_ReadOperandInt_02025de4(vm, &operands[0]);
    slotIndex = ScriptVm_ReadOperandInt_02025de4(vm, &operands[1]);
    saveBits = operands[2].value;
    position.x = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[3]);
    position.y = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[4]);
    position.z = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[5]);
    hidden = ScriptVm_ReadOperandInt_02025de4(vm, &operands[6]);
    FieldObject_CreateAtPosition_020a0b7c(func_ov001_0207f028(classIndex), (u16)slotIndex, (u16)saveBits, (u8)(u16)(saveBits >> 16), &position, hidden);
    return 1;
}
