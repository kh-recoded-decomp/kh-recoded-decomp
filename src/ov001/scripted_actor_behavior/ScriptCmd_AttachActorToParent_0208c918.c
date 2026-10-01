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

typedef struct ActorNode {
    u8 pad_00[4];
    u16 flags;
} ActorNode;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern void *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern void ActorSlot_AttachToParentByIndex_02035b4c(u16 childIndex, u16 parentIndex, void *attachData);
extern ActorNode *func_02036240(u16 actorId);
extern void AllocateSlotIfNull_02025964(ScriptContext *context, int index);
extern void func_ov001_02089db0(ActorObject *actor, int mode, const VecFx32 *position, int actorId);
extern void func_ov001_02089ee4(ActorObject *actor, ActorObject *owner, u32 actorId);
extern void ActorSlot_SetFlag8ByIndex_02036120(u16 index, BOOL enable);
extern const VecFx32 data_02053438;

int ScriptCmd_AttachActorToParent_0208c918(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int parentId;
    int mode;
    void *attachData;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    parentId = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    mode = ScriptVm_ReadOperandInt_02025de4(context, operands + 3);
    attachData = func_02025dac(context, operands + 2);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    parentId = ScriptCmd_ReturnValue_02025960(context, parentId);
    ActorSlot_AttachToParentByIndex_02035b4c(actorId, parentId, attachData);
    switch (mode) {
    case 1:
        if (parentId >= 3) {
            func_02036240(parentId)->flags |= 0x10;
        }
        break;
    case 2:
        func_02036240(actorId)->flags |= 8;
        break;
    }
    if (context->scene->actorObjects != NULL) {
        AllocateSlotIfNull_02025964(context, actorId);
        func_ov001_02089db0(context->scene->actorObjects[actorId], 0, &data_02053438, actorId);
        func_ov001_02089ee4(context->scene->actorObjects[actorId], context->scene->actorObjects[parentId], actorId);
    }
    ActorSlot_SetFlag8ByIndex_02036120(actorId, TRUE);
    return 1;
}
