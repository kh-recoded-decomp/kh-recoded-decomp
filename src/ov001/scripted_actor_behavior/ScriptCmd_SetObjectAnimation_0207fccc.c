#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f038(int groupIndex, int entryIndex);
extern void func_ov001_0207f8d0(void *object, int animationIndex);

int ScriptCmd_SetObjectAnimation_0207fccc(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    int animationIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);

    func_ov001_0207f8d0(func_ov001_0207f038(groupIndex, entryIndex), animationIndex);
    return 1;
}
