#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern s32 func_ov001_02063a38(void);
extern void func_ov001_020633a0(int setIndex);

int ScriptCmd_LoadFieldObjectSet_02064eec(void *context, ScriptOperand *operands)
{
    int setIndex;

    setIndex = ScriptVm_ReadOperandInt_02025de4(context, operands);
    if (func_ov001_02063a38() != 6) {
        func_ov001_020633a0(setIndex);
    }
    return 1;
}
