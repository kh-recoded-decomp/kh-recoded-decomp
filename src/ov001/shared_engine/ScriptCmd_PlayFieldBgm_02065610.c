#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void func_ov001_02064184(BOOL useAlternateTrack, int fadeFrames);

int ScriptCmd_PlayFieldBgm_02065610(void *context, ScriptOperand *operands)
{
    int useAlternateTrack;
    int fadeFrames;

    useAlternateTrack = ScriptVm_ReadOperandInt_02025de4(context, operands);
    fadeFrames = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    func_ov001_02064184(useAlternateTrack != 0, fadeFrames);
    return 1;
}
