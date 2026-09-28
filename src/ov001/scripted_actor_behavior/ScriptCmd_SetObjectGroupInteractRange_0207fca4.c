#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f028(int groupIndex);
extern void SetFieldOffset4c_0207f8cc(void *group, fx32 interactRange);

int ScriptCmd_SetObjectGroupInteractRange_0207fca4(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    fx32 interactRange = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 1);

    SetFieldOffset4c_0207f8cc(func_ov001_0207f028(groupIndex), interactRange);
    return 1;
}
