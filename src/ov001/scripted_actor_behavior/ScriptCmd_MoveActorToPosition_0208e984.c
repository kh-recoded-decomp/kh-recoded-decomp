#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    void **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern void func_ov001_0208aab4(void *actor, VecFx32 *destination, char *moveMotion, char *secondaryMotion);

int ScriptCmd_MoveActorToPosition_0208e984(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    char *moveMotion;
    char *secondaryMotion;
    VecFx32 destination;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    moveMotion = func_02025dac(context, operands + 3);
    secondaryMotion = func_02025dac(context, operands + 4);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    destination.x = ScriptVm_ReadOperandFx32_02025df8(context, operands + 1);
    destination.y = 0;
    destination.z = ScriptVm_ReadOperandFx32_02025df8(context, operands + 2);
    func_ov001_0208aab4(context->scene->actorObjects[actorId], &destination, moveMotion, secondaryMotion);
    return 1;
}
