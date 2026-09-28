#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorAlphaCommand {
    ScriptOperand operands[4];
    s32 unk_20;
    s32 framesRemaining;
} ActorAlphaCommand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(void *context, int value);
extern void ScriptCmd_SetElemField_02025e18(void *context, ActorAlphaCommand *command);
extern void func_ov001_0208e320(int actorId, int alpha, BOOL translucent);

int ScriptCmd_SetActorAlpha_0208e3b0(void *context, ActorAlphaCommand *command)
{
    int actorId;
    int duration;
    fx32 alpha;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[0]);
    duration = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[3]);
    alpha = ScriptVm_ReadOperandFx32_02025df8(context, &command->operands[1]);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    func_ov001_0208e320(actorId, alpha >> 12, duration != 0);
    if (duration == 0) {
        return 1;
    }
    command->operands[0].value = actorId;
    command->framesRemaining = duration;
    ScriptCmd_SetElemField_02025e18(context, command);
    return 0;
}
