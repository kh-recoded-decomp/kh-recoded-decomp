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
extern u8 SpawnPanelCollider_020a3998(void *owner, u16 kind, int tag, const VecFx32 *position);

int ScriptCmd_SpawnPanelCollider_020a202c(void *vm, ScriptOperand *operands)
{
    int tableIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int kind = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    int tag = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);
    VecFx32 position;

    position.x = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 3);
    position.y = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 4);
    position.z = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 5);
    SpawnPanelCollider_020a3998(func_ov001_02087214(tableIndex), kind, tag, &position);
    return 1;
}
