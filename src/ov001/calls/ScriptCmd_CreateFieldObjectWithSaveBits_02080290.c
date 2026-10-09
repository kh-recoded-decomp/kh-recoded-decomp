#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

typedef struct CreateFieldObjectWithSaveBitsArgs {
    ScriptOperand objectClassIndex;
    ScriptOperand slotIndex;
    u8 pad_10[4];
    u32 saveBits;
} CreateFieldObjectWithSaveBitsArgs;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f028(int index);
extern void *FieldObject_CreateWithSaveBits_02082038(void *objectClass, u16 slotIndex,
                                            u16 saveBitOffset, u8 saveBitCount);

int ScriptCmd_CreateFieldObjectWithSaveBits_02080290(void *vm, CreateFieldObjectWithSaveBitsArgs *args)
{
    int objectClassIndex = ScriptVm_ReadOperandInt_02025de4(vm, &args->objectClassIndex);
    int slotIndex = ScriptVm_ReadOperandInt_02025de4(vm, &args->slotIndex);
    u32 saveBits = args->saveBits;
    int saveBitOffset = (u16)saveBits;
    int saveBitCount = (u8)(u16)(saveBits >> 16);

    FieldObject_CreateWithSaveBits_02082038(func_ov001_0207f028(objectClassIndex),
                                   (u16)slotIndex,
                                   (u16)saveBitOffset,
                                   (u8)saveBitCount);
    return TRUE;
}
