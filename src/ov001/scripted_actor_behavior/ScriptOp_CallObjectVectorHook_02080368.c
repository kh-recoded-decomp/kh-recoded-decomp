#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, void *operand);
extern void *func_ov001_0207f038(u32 group, u32 index);
extern void func_ov001_0207f800(void *object, VecFx32 *value);

int ScriptOp_CallObjectVectorHook_02080368(void *vm, ScriptOperand *operands)
{
    int group = ScriptVm_ReadOperandInt_02025de4(vm, &operands[0]);
    int index = ScriptVm_ReadOperandInt_02025de4(vm, &operands[1]);
    VecFx32 value;

    value.x = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[2]);
    value.y = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[3]);
    value.z = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[4]);
    func_ov001_0207f800(func_ov001_0207f038(group, index), &value);
    return 1;
}
