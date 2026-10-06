#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u16 unk_02;
    u32 rawValue;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f050(int groupIndex);
extern void CreateElevatorObject(void *group, u16 kind, u16 saveBitOffset, u8 saveBitCount,
                                VecFx32 *position, VecFx32 *rotation);

int func_ov006_020a0604(void *vm, ScriptOperand *operands)
{
    VecFx32 position;
    VecFx32 rotation;
    int groupIndex = ScriptVm_ReadOperandInt(vm, &operands[0]);
    int kind = ScriptVm_ReadOperandInt(vm, &operands[1]);
    u32 saveBits = operands[2].rawValue;

    position.x = ScriptVm_ReadOperandFx32(vm, &operands[3]);
    position.y = ScriptVm_ReadOperandFx32(vm, &operands[4]);
    position.z = ScriptVm_ReadOperandFx32(vm, &operands[5]);
    rotation.x = ScriptVm_ReadOperandFx32(vm, &operands[6]);
    rotation.y = ScriptVm_ReadOperandFx32(vm, &operands[7]);
    rotation.z = ScriptVm_ReadOperandFx32(vm, &operands[8]);
    CreateElevatorObject(func_ov001_0207f050(groupIndex), kind, saveBits, (u16)(saveBits >> 16),
                        &position, &rotation);
    return 1;
}
