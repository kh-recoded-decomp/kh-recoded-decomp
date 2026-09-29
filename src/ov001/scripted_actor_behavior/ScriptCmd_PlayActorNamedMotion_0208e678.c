#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern char *func_02025dac(void *context, ScriptOperand *operand);
extern void func_ov001_020889ec(int actorIndex, int motionId, int mode, char *motionName);

int ScriptCmd_PlayActorNamedMotion_0208e678(void *context, ScriptOperand *operands)
{
    int actorIndex;
    char *motionName;
    int motionId;
    int mode;

    actorIndex = ScriptVm_ReadOperandInt_02025de4(context, operands);
    motionName = func_02025dac(context, operands + 1);
    motionId = ScriptVm_ReadOperandInt_02025de4(context, operands + 2);
    mode = 0;
    if (operands[3].type != 0) {
        mode = ScriptVm_ReadOperandInt_02025de4(context, operands + 3);
    }
    func_ov001_020889ec(actorIndex, motionId, mode, motionName);
    return 1;
}
