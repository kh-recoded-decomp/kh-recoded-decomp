#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_02084958(u16 entryCount);
extern void func_ov001_0207ee04(int groupIndex, void *group);

int ScriptCmd_CreateObjectGroupKind9_02080404(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryCount = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);

    func_ov001_0207ee04(groupIndex, func_ov001_02084958(entryCount));
    return 1;
}
