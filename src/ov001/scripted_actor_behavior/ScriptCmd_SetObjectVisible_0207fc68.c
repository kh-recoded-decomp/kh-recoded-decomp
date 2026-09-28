#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f038(int groupIndex, int entryIndex);
extern void func_ov001_0207f6f4(void *object, BOOL visible);

int ScriptCmd_SetObjectVisible_0207fc68(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    int visible = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);

    func_ov001_0207f6f4(func_ov001_0207f038(groupIndex, entryIndex), visible != 0);
    return 1;
}
