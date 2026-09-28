#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void ActorChannel_ConfigureAndPlay_0208b9cc(u32 channelId, u32 param2, s32 resetMode);

int ScriptCmd_PlayActorChannel_0208d560(void *context, ScriptOperand *operands)
{
    u32 channelId;
    u32 param2;
    int resetMode;

    channelId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    param2 = ScriptVm_ReadOperandInt_02025de4(context, operands + 2);
    resetMode = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    ActorChannel_ConfigureAndPlay_0208b9cc(channelId, param2, resetMode != 0);
    return 1;
}
