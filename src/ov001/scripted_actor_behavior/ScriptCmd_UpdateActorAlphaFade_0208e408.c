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
extern void *func_02036240(u16 actorId);
extern fx32 EvaluateInterpolationCurve_02025718(int curveType, u32 duration, int framesRemaining);
extern fx32 ScaleAroundPivot_020257b0(fx32 progress, fx32 target, fx32 start);
extern void func_ov001_0208e320(int actorId, int alpha, BOOL translucent);
extern void ScriptCmd_SetElemField_02025e18(void *context, ActorAlphaCommand *command);

int ScriptCmd_UpdateActorAlphaFade_0208e408(void *context, ActorAlphaCommand *command)
{
    int actorId;
    int duration;
    fx32 startAlpha;
    fx32 targetAlpha;
    fx32 progress;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[0]);
    duration = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[3]);
    startAlpha = ScriptVm_ReadOperandFx32_02025df8(context, &command->operands[1]);
    targetAlpha = ScriptVm_ReadOperandFx32_02025df8(context, &command->operands[2]);
    func_02036240(actorId);
    if (--command->framesRemaining == 0) {
        func_ov001_0208e320(actorId, targetAlpha >> 12, FALSE);
        return 1;
    }
    progress = EvaluateInterpolationCurve_02025718(2, duration, command->framesRemaining);
    func_ov001_0208e320(actorId, ScaleAroundPivot_020257b0(progress, targetAlpha, startAlpha) >> 12, TRUE);
    ScriptCmd_SetElemField_02025e18(context, command);
    return 0;
}
