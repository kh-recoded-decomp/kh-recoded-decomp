#include "nitro/types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f028(int index);
extern void *FieldObject_CreateAtOrigin_020a0c78(void *objectClass, int slotIndex, u16 saveBitOffset, u8 saveBitCount);

int ScriptCmd_CreateObjectAtOrigin_020a0660(void *vm, ScriptOperand *operands)
{
    int classIndex;
    int slotIndex;
    u32 saveBits;

    classIndex = ScriptVm_ReadOperandInt_02025de4(vm, &operands[0]);
    slotIndex = ScriptVm_ReadOperandInt_02025de4(vm, &operands[1]);
    saveBits = operands[2].value;
    FieldObject_CreateAtOrigin_020a0c78(func_ov001_0207f028(classIndex), (u16)slotIndex, (u16)saveBits, (u8)(u16)(saveBits >> 16));
    return 1;
}
