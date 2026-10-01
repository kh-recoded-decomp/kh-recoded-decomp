#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    u32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

typedef struct FieldObjectSpawn {
    int typeId;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 variant;
    VecFx32 position;
} FieldObjectSpawn;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern void *func_ov001_02080ce4(u16 slotIndex, FieldObjectSpawn *spawn);
extern void func_ov001_0207ee04(int index, void *object);

BOOL ScriptCmd_SpawnFieldObjectInSlot_0207fb54(ScriptContext *context, ScriptOperand *operands)
{
    FieldObjectSpawn spawn;
    int index = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int slotIndex = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);

    spawn.saveBitOffset = ScriptVm_ReadOperandInt_02025de4(context, &operands[2]);
    spawn.saveBitCount = ScriptVm_ReadOperandInt_02025de4(context, &operands[3]);
    spawn.typeId = ScriptVm_ReadOperandInt_02025de4(context, &operands[4]);
    spawn.variant = ScriptVm_ReadOperandInt_02025de4(context, &operands[5]);
    spawn.position.x = ScriptVm_ReadOperandFx32_02025df8(context, &operands[6]);
    spawn.position.y = ScriptVm_ReadOperandFx32_02025df8(context, &operands[7]);
    spawn.position.z = ScriptVm_ReadOperandFx32_02025df8(context, &operands[8]);
    func_ov001_0207ee04(index, func_ov001_02080ce4(slotIndex, &spawn));
    return TRUE;
}
