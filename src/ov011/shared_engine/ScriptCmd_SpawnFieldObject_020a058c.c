#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s32 type;
    u32 value;
} ScriptOperand;

typedef struct SpawnExtra {
    s32 kind;
    union {
        struct {
            u8 first;
            u8 second;
        } pair;
        struct {
            u16 id;
            u8 arg;
        } wide;
    } data;
} SpawnExtra;

extern s32 ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f028(int index);
extern void *FieldObject_CreateAt_020a1054(void *objectClass, u16 slotIndex, u16 saveBitOffset,
                                           u8 saveBitCount, VecFx32 *position, SpawnExtra *extra);

BOOL ScriptCmd_SpawnFieldObject_020a058c(void *vm, ScriptOperand *op)
{
    VecFx32 position;
    SpawnExtra extra;
    u16 saveBitOffset;
    u8 saveBitCount;
    int slotIndex;
    int classIndex;

    classIndex = ScriptVm_ReadOperandInt_02025de4(vm, &op[0]);
    slotIndex = ScriptVm_ReadOperandInt_02025de4(vm, &op[1]);
    saveBitOffset = op[2].value;
    saveBitCount = (u16)(op[2].value >> 16);

    position.x = ScriptVm_ReadOperandFx32_02025df8(vm, &op[3]);
    position.y = ScriptVm_ReadOperandFx32_02025df8(vm, &op[4]);
    position.z = ScriptVm_ReadOperandFx32_02025df8(vm, &op[5]);
    extra.kind = ScriptVm_ReadOperandInt_02025de4(vm, &op[6]);
    switch (extra.kind) {
    case 0:
        extra.data.pair.first = ScriptVm_ReadOperandInt_02025de4(vm, &op[7]);
        break;
    case 1:
        extra.data.wide.id = ScriptVm_ReadOperandInt_02025de4(vm, &op[7]);
        extra.data.wide.arg = ScriptVm_ReadOperandInt_02025de4(vm, &op[8]);
        break;
    case 2:
        extra.data.pair.first = ScriptVm_ReadOperandInt_02025de4(vm, &op[7]);
        extra.data.pair.second = ScriptVm_ReadOperandInt_02025de4(vm, &op[8]);
        break;
    case 3:
        extra.data.pair.first = ScriptVm_ReadOperandInt_02025de4(vm, &op[7]);
        extra.data.pair.second = ScriptVm_ReadOperandInt_02025de4(vm, &op[8]);
        break;
    case 4:
        extra.data.pair.first = ScriptVm_ReadOperandInt_02025de4(vm, &op[7]);
        extra.data.pair.second = ScriptVm_ReadOperandInt_02025de4(vm, &op[8]);
        break;
    case 5:
        extra.data.pair.first = ScriptVm_ReadOperandInt_02025de4(vm, &op[7]);
        extra.data.pair.second = ScriptVm_ReadOperandInt_02025de4(vm, &op[8]);
        break;
    }
    FieldObject_CreateAt_020a1054(func_ov001_0207f028(classIndex), slotIndex, saveBitOffset, saveBitCount,
                                  &position, &extra);
    return TRUE;
}
