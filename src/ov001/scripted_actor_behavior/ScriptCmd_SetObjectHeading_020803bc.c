#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f038(int groupIndex, int entryIndex);
extern s32 func_02023dbc(s32 numerator, s32 denominator);
extern void func_ov001_0207f7c0(void *object, u16 heading);

int ScriptCmd_SetObjectHeading_020803bc(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    int degrees = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);
    void *object = func_ov001_0207f038(groupIndex, entryIndex);

    func_ov001_0207f7c0(object, func_02023dbc(degrees << 16, 360));
    return 1;
}
