#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, void *operand);
extern void func_ov021_020af544(int slot, const VecFx32 *value);

int ScriptOp_SetVector4_02065574(void *vm, ScriptOperand *operands)
{
    VecFx32 value;

    value.x = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[0]);
    value.y = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[1]);
    value.z = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[2]);
    func_ov021_020af544(4, &value);
    return 1;
}
