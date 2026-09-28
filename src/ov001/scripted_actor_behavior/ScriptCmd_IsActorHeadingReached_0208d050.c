#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct Actor {
    u8 pad_000[0xef8];
    s32 heading;
    s32 targetHeading;
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
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);

int ScriptCmd_IsActorHeadingReached_0208d050(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    Actor *actor;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    actor = context->scene->actorObjects[actorId];
    if (actor->heading == actor->targetHeading) {
        return 1;
    }
    return 0;
}
