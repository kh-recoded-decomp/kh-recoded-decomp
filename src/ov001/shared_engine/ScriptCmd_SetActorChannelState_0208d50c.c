#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern void ActorChannel_SetStateFields_0208b870(u32 state, u32 enabled);

int ScriptCmd_SetActorChannelState_0208d50c(void *context, ScriptOperand *operands)
{
    u32 state;
    int enabled;

    state = ScriptVm_ReadOperandInt_02025de4(context, operands);
    enabled = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    ActorChannel_SetStateFields_0208b870(state, enabled != 0);
    return 1;
}
