#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern s32 func_ov001_02063a38(void);
extern void func_ov030_020bb460(BOOL enable);
extern void SetFlagBit4(BOOL enable);
extern void DrawSceneGroups(BOOL enable);
extern void SetOrClearStatusBit2(BOOL enable);

int ScriptCmd_SetSceneFlagBit2(void *context, ScriptOperand *operands)
{
    BOOL enable = ScriptVm_ReadOperandInt(context, operands) ? TRUE : FALSE;

    switch (func_ov001_02063a38()) {
    case 4:
        func_ov030_020bb460(enable);
        break;
    case 7:
        SetFlagBit4(enable);
        break;
    case 6:
        DrawSceneGroups(enable);
        break;
    default:
        SetOrClearStatusBit2(enable);
        break;
    }
    return 1;
}
