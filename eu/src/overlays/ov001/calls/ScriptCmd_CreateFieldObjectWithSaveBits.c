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

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f050(int index);
extern void *FieldObject_CreateWithSaveBits(void *objectClass, u16 slotIndex,
                                            u16 saveBitOffset, u8 saveBitCount);

int ScriptCmd_CreateFieldObjectWithSaveBits(void *vm, CreateFieldObjectWithSaveBitsArgs *args)
{
    int objectClassIndex = ScriptVm_ReadOperandInt(vm, &args->objectClassIndex);
    int slotIndex = ScriptVm_ReadOperandInt(vm, &args->slotIndex);
    u32 saveBits = args->saveBits;
    int saveBitOffset = (u16)saveBits;
    int saveBitCount = (u8)(u16)(saveBits >> 16);

    FieldObject_CreateWithSaveBits(func_ov001_0207f050(objectClassIndex),
                                   (u16)slotIndex,
                                   (u16)saveBitOffset,
                                   (u8)saveBitCount);
    return TRUE;
}
