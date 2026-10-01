#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorObject ActorObject;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    ActorObject **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern void *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern void StartActorMotionTo_0208a4b8(ActorObject *actor, const char *name, const VecFx32 *target, int duration, int extra);

int ScriptCmd_StartActorRotation_0208dc4c(ScriptContext *context, ScriptOperand *operands)
{
    int slot = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int degX = ScriptVm_ReadOperandInt_02025de4(context, &operands[2]);
    int degY = ScriptVm_ReadOperandInt_02025de4(context, &operands[3]);
    int degZ = ScriptVm_ReadOperandInt_02025de4(context, &operands[4]);
    int duration = ScriptVm_ReadOperandInt_02025de4(context, &operands[5]);
    int extra = ScriptVm_ReadOperandInt_02025de4(context, &operands[6]);
    const char *name = func_02025dac(context, &operands[1]);
    int index = ScriptCmd_ReturnValue_02025960(context, slot);
    VecFx32 angles;

    angles.x = degX * 0xb6;
    angles.y = degY * 0xb6;
    angles.z = degZ * 0xb6;
    StartActorMotionTo_0208a4b8(context->scene->actorObjects[index], name, &angles, duration, extra);
    return 1;
}
