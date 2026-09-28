#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f038(int groupIndex, int entryIndex);
extern void func_ov001_0207fa98(void *object, fx32 cullRadius);

int ScriptCmd_SetObjectCullRadius_02080744(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    fx32 cullRadius = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 2);

    func_ov001_0207fa98(func_ov001_0207f038(groupIndex, entryIndex), cullRadius);
    return 1;
}
