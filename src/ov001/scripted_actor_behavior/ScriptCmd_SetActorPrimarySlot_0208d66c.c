#include "nitro/types.h"

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
extern int ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern void ActorObject_SetPrimarySlot_0208a6f4(void *actor, u32 handler, u32 arg);

int ScriptCmd_SetActorPrimarySlot_0208d66c(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    u32 arg;
    u32 handler;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    arg = ScriptVm_ReadOperandInt_02025de4(context, operands + 2);
    handler = ScriptVm_ReadOperandFx32_02025df8(context, operands + 1);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    ActorObject_SetPrimarySlot_0208a6f4(context->scene->actorObjects[actorId], handler, arg);
    return 1;
}
