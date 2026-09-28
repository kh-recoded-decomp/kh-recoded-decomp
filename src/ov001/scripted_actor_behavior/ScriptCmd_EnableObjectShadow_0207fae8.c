#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f038(int groupIndex, int entryIndex);
extern void func_ov001_0207f8fc(void *object, BOOL enable, s16 shadowScale, BOOL useVolume);

int ScriptCmd_EnableObjectShadow_0207fae8(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    fx32 shadowScale = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 2);
    int useVolume = ScriptVm_ReadOperandInt_02025de4(vm, operands + 3);

    func_ov001_0207f8fc(func_ov001_0207f038(groupIndex, entryIndex), TRUE, (s16)shadowScale, useVolume);
    return 1;
}
