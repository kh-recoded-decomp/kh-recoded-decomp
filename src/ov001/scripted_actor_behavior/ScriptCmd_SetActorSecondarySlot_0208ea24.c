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

typedef struct SecondarySlot {
    s32 first;
    s32 second;
} SecondarySlot;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern void ActorObject_ResetSecondarySlots_0208a704(void *actor);
extern void ActorObject_SetSecondarySlot_0208a724(void *actor, const void *src, int index);

int ScriptCmd_SetActorSecondarySlot_0208ea24(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int slotIndex;
    SecondarySlot slot;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    if (operands[1].type == 0) {
        ActorObject_ResetSecondarySlots_0208a704(context->scene->actorObjects[actorId]);
    } else {
        slotIndex = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
        slot.first = ScriptVm_ReadOperandInt_02025de4(context, &operands[2]);
        slot.second = ScriptVm_ReadOperandInt_02025de4(context, &operands[3]);
        ActorObject_SetSecondarySlot_0208a724(context->scene->actorObjects[actorId], &slot, slotIndex);
    }
    return 1;
}
