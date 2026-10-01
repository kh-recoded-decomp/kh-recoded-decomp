#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u8 pad_00[0x7c];
    void *model;
} ActorNode;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern ActorNode *func_02036240(u16 actorId);
extern void SetWorldObjectProbeSphere_02036198(u16 index, BOOL enable, fx32 radius);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, int polygonId);
extern void ScriptCmd_SetElemField_02025e18(ScriptContext *context, ScriptOperand *operands);

int ScriptCmd_SetActorProbeSphere_0208ca94(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int waitFrames;
    fx32 radius;
    ActorNode *node;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    waitFrames = ScriptVm_ReadOperandInt_02025de4(context, operands + 3);
    radius = ScriptVm_ReadOperandFx32_02025df8(context, operands + 1);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    if (radius == 0) {
        SetWorldObjectProbeSphere_02036198(actorId, FALSE, 0);
    } else {
        node = func_02036240(actorId);
        SetWorldObjectProbeSphere_02036198(actorId, TRUE, radius);
        Model_SetAllPolygonIds_0201a8c0(node->model, 0x3f);
    }
    if (waitFrames == 0) {
        return 1;
    }
    operands[0].value = actorId;
    operands[4].value = waitFrames;
    ScriptCmd_SetElemField_02025e18(context, operands);
    return 0;
}
