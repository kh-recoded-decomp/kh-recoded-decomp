#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorObject {
    u8 pad_000[0xef4];
    u32 flags;
} ActorObject;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    ActorObject **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

typedef struct ActorNode {
    u8 pad_00[0xa8];
    u8 position[12];
} ActorNode;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern void AllocateSlotIfNull_02025964(ScriptContext *context, int index);
extern void *func_ov001_0206e6c0(int partyIndex);
extern void Actor_AttachSource_02089e94(ActorObject *actor, int mode, void *source);
extern ActorNode *func_02036240(u16 actorId);
extern void func_ov001_02089db0(ActorObject *actor, int mode, void *position, int actorId);

int ScriptCmd_AttachActorObject_0208e524(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    AllocateSlotIfNull_02025964(context, actorId);
    if (actorId < 3) {
        Actor_AttachSource_02089e94(context->scene->actorObjects[actorId], actorId, func_ov001_0206e6c0(actorId));
    } else {
        ActorNode *node = func_02036240(actorId);
        func_ov001_02089db0(context->scene->actorObjects[actorId], 0, node->position, actorId);
    }
    context->scene->actorObjects[actorId]->flags |= 0x10000;
    return 1;
}
