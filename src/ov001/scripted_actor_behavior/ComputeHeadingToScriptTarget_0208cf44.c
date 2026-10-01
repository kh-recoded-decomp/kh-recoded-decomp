#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorNode;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern int func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern ActorNode *func_02036240(u16 actorId);
extern int func_02036564(int location, VecFx32 *out);
extern u16 FixedPointAtan2_020062bc(int vertical, int horizontal);

u32 ComputeHeadingToScriptTarget_0208cf44(ScriptContext *context, ScriptOperand *target, int actorId)
{
    VecFx32 delta;
    VecFx32 targetPos;

    if (target->type == 1) {
        targetPos = func_02036240(ScriptCmd_ReturnValue_02025960(context, ScriptVm_ReadOperandInt_02025de4(context, target)))->position;
    } else if (target->type == 2) {
        func_02036564(func_02025dac(context, target), &targetPos);
    } else {
        return 1;
    }
    delta = func_02036240(actorId)->position;
    delta.x = targetPos.x - delta.x;
    delta.z = targetPos.z - delta.z;
    return (u16)(0x13fff - FixedPointAtan2_020062bc(delta.z, delta.x));
}
