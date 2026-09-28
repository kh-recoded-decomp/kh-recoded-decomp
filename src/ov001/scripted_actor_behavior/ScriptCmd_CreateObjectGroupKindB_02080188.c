#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_020825e0(u16 entryCount);
extern void func_ov001_0207ee04(int groupIndex, void *group);

int ScriptCmd_CreateObjectGroupKindB_02080188(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryCount = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);

    func_ov001_0207ee04(groupIndex, func_ov001_020825e0(entryCount));
    return 1;
}
