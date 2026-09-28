#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern BOOL func_ov001_0207d3d8(int indicatorKind, u16 frameNumber);
extern BOOL func_ov001_0207d440(u32 value);

int ScriptCmd_ShowHudIndicator_0206572c(void *context, ScriptOperand *operands)
{
    int indicatorKind;
    u32 frameNumber;

    indicatorKind = ScriptVm_ReadOperandInt_02025de4(context, operands);
    frameNumber = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    func_ov001_0207d3d8(indicatorKind, frameNumber);
    func_ov001_0207d440(1);
    return 0;
}
