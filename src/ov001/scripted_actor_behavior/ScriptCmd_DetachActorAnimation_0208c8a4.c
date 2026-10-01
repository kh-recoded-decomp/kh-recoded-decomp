#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

typedef struct Actor {
    u8 pad_000[0xd18];
    u32 unk_D18;
    u8 pad_D1C[0x1d8];
    u32 flags;
} Actor;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    Actor **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

typedef struct ActorModel {
    u8 pad_00[2];
    s16 animationId;
    u8 pad_04[8];
    void *animationObj;
    u8 pad_10[0x10];
    u8 renderObj[1];
} ActorModel;

typedef struct ActorModelSlot {
    u8 pad_00[4];
    ActorModel model;
} ActorModelSlot;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern u32 ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern ActorModelSlot *func_02036240(u16 index);
extern void func_ov001_0208a0fc(Actor *actor);
extern void RemoveAnimationFromRenderObject_02018850(void *renderObj, void *animationObj);
extern void ActorSlot_UnlinkByIndex_02035c28(u16 index);

int ScriptCmd_DetachActorAnimation_0208c8a4(ScriptContext *context, ScriptOperand *operands)
{
    u32 actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    ActorModelSlot *slot = func_02036240(actorId);
    Actor *actor;
    ActorModel *model;

    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    actor = context->scene->actorObjects[actorId];
    if (actor != NULL && (actor->unk_D18 != 0 || (actor->flags & 0x4000) != 0)) {
        func_ov001_0208a0fc(actor);
    }
    model = &slot->model;
    if (model->animationObj != NULL) {
        RemoveAnimationFromRenderObject_02018850(model->renderObj, model->animationObj);
        model->animationId = -1;
        model->animationObj = NULL;
    }
    ActorSlot_UnlinkByIndex_02035c28(actorId);
    return 1;
}
