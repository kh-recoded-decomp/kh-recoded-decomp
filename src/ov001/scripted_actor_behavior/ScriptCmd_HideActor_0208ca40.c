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

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern u32 ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern void SetRecordSlotFlagBit3_02036120(u16 index, int flag);
extern void ActorObject_SetFlagBit3IfBit14Set_0208a48c(Actor *actor, int enable);

int ScriptCmd_HideActor_0208ca40(ScriptContext *context, ScriptOperand *operands)
{
    u32 actorId;
    Actor *actor;

    actorId = ScriptCmd_ReturnValue_02025960(context, ScriptVm_ReadOperandInt_02025de4(context, operands));
    SetRecordSlotFlagBit3_02036120(actorId, 0);
    actor = context->scene->actorObjects[actorId];
    if (actor != NULL && (actor->unk_D18 != 0 || (actor->flags & 0x4000) != 0)) {
        ActorObject_SetFlagBit3IfBit14Set_0208a48c(actor, 0);
    }
    return 1;
}
