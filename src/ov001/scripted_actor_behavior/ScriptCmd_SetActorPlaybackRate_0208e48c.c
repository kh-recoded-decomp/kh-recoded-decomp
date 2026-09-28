#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *context, ScriptOperand *operand);
extern u32 ScriptCmd_ReturnValue_02025960(void *context, int value);
extern void func_020367d0(u32 actorId, s32 rate);

int ScriptCmd_SetActorPlaybackRate_0208e48c(void *context, ScriptOperand *operands)
{
    int actorId;
    fx32 rate;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    rate = ScriptVm_ReadOperandFx32_02025df8(context, operands + 1);
    func_020367d0(ScriptCmd_ReturnValue_02025960(context, actorId) & 0xffff, (s16)rate);
    return 1;
}
