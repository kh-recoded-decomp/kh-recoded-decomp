#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_02087224(int groupIndex, int entryIndex);
extern void func_ov001_02087258(void *object, BOOL visible);

int ScriptCmd_SetAuxObjectVisible_0207ffbc(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    int visible = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);

    func_ov001_02087258(func_ov001_02087224(groupIndex, entryIndex), visible != 0);
    return 1;
}
