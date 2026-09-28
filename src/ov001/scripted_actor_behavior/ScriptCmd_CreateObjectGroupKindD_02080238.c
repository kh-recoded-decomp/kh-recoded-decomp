#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov001_02081fac(u16 entryCount, int resourceId, fx32 width, fx32 depth);
extern void func_ov001_0207ee04(int groupIndex, void *group);

int ScriptCmd_CreateObjectGroupKindD_02080238(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryCount = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    int resourceId = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);
    fx32 width = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 3);
    fx32 depth = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 4);

    func_ov001_0207ee04(groupIndex, func_ov001_02081fac(entryCount, resourceId, width, depth));
    return 1;
}
