#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
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

typedef struct ActorNode {
    u8 pad_00[4];
    u8 fadeState[0xd8];
    u8 blendTable[4];
} ActorNode;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern void Script_ResolveMotionNameAndId_0208cc38(ScriptContext *context, ScriptOperand *operands, int actorId,
                                                   int *outMotionId, char *outMotionName);
extern void func_ov001_0208a54c(Actor *actor, char *motionName, int motionId, int layer, int frameCount);
extern ActorNode *func_02036240(u16 actorId);
extern void BlendToAnimationTrack_0202f374(void *state, u16 trackIndex, void *table, s16 blendIndex, int frameCount);

int ScriptCmd_PlayActorMotionOrBlend_0208ccbc(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int layer;
    int frameCount;
    int motionId;
    char motionName[64];
    ActorNode *node;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    layer = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    frameCount = ScriptVm_ReadOperandInt_02025de4(context, operands + 4);
    motionId = -1;
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    if (context->scene->actorObjects[actorId] != NULL
        && (context->scene->actorObjects[actorId]->unk_D18 != 0
            || (context->scene->actorObjects[actorId]->flags & 0x4000) != 0)) {
        motionName[0] = '\0';
        Script_ResolveMotionNameAndId_0208cc38(context, operands, actorId, &motionId, motionName);
        func_ov001_0208a54c(context->scene->actorObjects[actorId], motionName, motionId, layer, frameCount);
    } else {
        node = func_02036240(actorId);
        motionId = ScriptVm_ReadOperandInt_02025de4(context, operands + 3);
        BlendToAnimationTrack_0202f374(node->fadeState, layer, node->blendTable, motionId, frameCount);
    }
    return 1;
}
