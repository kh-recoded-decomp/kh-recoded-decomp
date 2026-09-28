#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct OverlayFadeCommand {
    ScriptOperand operands[4];
    s32 unk_20;
    s32 framesRemaining;
} OverlayFadeCommand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *context, ScriptOperand *operand);
extern void ScriptCmd_SetElemField_02025e18(void *context, OverlayFadeCommand *command);
extern fx32 EvaluateInterpolationCurve_02025718(int curve, u32 duration, int remaining);
extern fx32 ScaleAroundPivot_020257b0(fx32 progress, fx32 target, fx32 start);
extern void func_ov001_020889d0(u32 colorIndex, u32 alpha);

int ScriptCmd_UpdateScreenOverlayFade_0208e610(void *context, OverlayFadeCommand *command)
{
    u32 colorIndex;
    fx32 startAlpha;
    fx32 targetAlpha;
    u32 duration;
    int remaining;
    fx32 progress;
    fx32 alpha;

    colorIndex = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[0]);
    startAlpha = ScriptVm_ReadOperandFx32_02025df8(context, &command->operands[1]);
    targetAlpha = ScriptVm_ReadOperandFx32_02025df8(context, &command->operands[2]);
    duration = ScriptVm_ReadOperandInt_02025de4(context, &command->operands[3]);
    remaining = command->framesRemaining - 1;
    command->framesRemaining = remaining;
    if (remaining == 0) {
        func_ov001_020889d0(colorIndex, targetAlpha >> 12);
        return 1;
    }
    progress = EvaluateInterpolationCurve_02025718(2, duration, remaining);
    alpha = ScaleAroundPivot_020257b0(progress, targetAlpha, startAlpha);
    func_ov001_020889d0(colorIndex, alpha >> 12);
    ScriptCmd_SetElemField_02025e18(context, command);
    return 0;
}
