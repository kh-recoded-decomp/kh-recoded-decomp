#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov036_020bd6bc(u32 screen, int level, int duration);

int ScriptCmd_StartBrightnessFade_020be62c(void *context, ScriptOperand *operands)
{
    int level = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int duration = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
    int screen = ScriptVm_ReadOperandInt_02025de4(context, &operands[2]);

    func_ov036_020bd6bc(screen, level, duration);
    return 1;
}
