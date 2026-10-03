#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov001_02087214(int tableIndex);
extern u8 SpawnLinkedObject_020a3328(void *owner, u16 kind, int tag, u16 linkId, u8 linkSlot,
                                     const VecFx32 *position, s8 sizeX, s8 sizeY, s16 rotX, s16 rotY, s16 rotZ,
                                     s8 unused, s8 linkIndex, u32 options);

int ScriptCmd_SpawnLinkedObject_020a1e10(void *vm, ScriptOperand *operands)
{
    int tableIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int kind = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    int tag = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);
    u16 linkId;
    u8 linkSlot;
    VecFx32 position;
    int sizeX;
    int sizeY;
    int rotX;
    int rotY;
    int rotZ;
    int unused;
    int linkIndex;
    int options;

    if (operands[3].type == 0) {
        linkId = 0xffff;
        linkSlot = 0xff;
    } else {
        linkId = operands[3].value;
        linkSlot = (u16)((u32)operands[3].value >> 16);
    }
    position.x = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 4);
    position.y = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 5);
    position.z = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 6);
    sizeX = ScriptVm_ReadOperandInt_02025de4(vm, operands + 7);
    sizeY = ScriptVm_ReadOperandInt_02025de4(vm, operands + 8);
    rotX = ScriptVm_ReadOperandInt_02025de4(vm, operands + 9);
    rotY = ScriptVm_ReadOperandInt_02025de4(vm, operands + 10);
    rotZ = ScriptVm_ReadOperandInt_02025de4(vm, operands + 11);
    unused = ScriptVm_ReadOperandInt_02025de4(vm, operands + 12);
    linkIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 13);
    options = ScriptVm_ReadOperandInt_02025de4(vm, operands + 14);

    SpawnLinkedObject_020a3328(func_ov001_02087214(tableIndex), kind, tag, linkId, linkSlot, &position, sizeX,
                               sizeY, rotX, rotY, rotZ, unused, linkIndex, options);
    return 1;
}
