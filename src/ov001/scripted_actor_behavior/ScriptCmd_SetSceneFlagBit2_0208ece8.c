#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern s32 func_ov001_02063a38(void);
extern void func_ov030_020bb440(BOOL enable);
extern void SetFlagBit4_020bc748(BOOL enable);
extern void func_ov031_020bb2d4(BOOL enable);
extern void SetOrClearStatusBit2_020bb2a8(BOOL enable);

int ScriptCmd_SetSceneFlagBit2_0208ece8(void *context, ScriptOperand *operands)
{
    BOOL enable = ScriptVm_ReadOperandInt_02025de4(context, operands) ? TRUE : FALSE;

    switch (func_ov001_02063a38()) {
    case 4:
        func_ov030_020bb440(enable);
        break;
    case 7:
        SetFlagBit4_020bc748(enable);
        break;
    case 6:
        func_ov031_020bb2d4(enable);
        break;
    default:
        SetOrClearStatusBit2_020bb2a8(enable);
        break;
    }
    return 1;
}
