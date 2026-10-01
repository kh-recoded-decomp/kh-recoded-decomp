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

typedef struct ActorSlot {
    int animation;
    int param;
} ActorSlot;

extern ScriptOperand data_ov001_0209e430;
extern char data_ov001_020a0230[];
extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern u8 *func_02036240(u16 actorId);
extern void *func_02036810(u16 actorId);
extern void *QueryLinkTarget_02080a78(void *owner);
extern void SetFieldOffset5aIfFlag_020814c4(void *self, int value, int flag);
extern int func_ov001_0208cf44(ScriptContext *context, ScriptOperand *target, int actorId);
extern void ActorObject_SetSecondarySlot_0208a724(void *actor, const void *src, int index);
extern void func_ov001_0208a73c(void *actorObject, int heading, char *turnAnimation, char *followAnimation);

int ScriptCmd_FaceTargetWithAnims_0208ed2c(ScriptContext *context, ScriptOperand *operands)
{
    int actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    int forwardAnim = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    int backwardAnim = ScriptVm_ReadOperandInt_02025de4(context, operands + 2);
    ScriptOperand target = data_ov001_0209e430;
    u16 current = *(u16 *)(func_02036240(actorId) + 0x80);
    int heading = func_ov001_0208cf44(context, &target, actorId);

    if (current == heading) {
        void *link = QueryLinkTarget_02080a78(func_02036810(actorId));
        int diff = *(u16 *)((u8 *)link + 0x4c) - current;
        int wrapped = (u16)diff;
        if (wrapped >= 0x8000) {
            forwardAnim = backwardAnim;
        }
        SetFieldOffset5aIfFlag_020814c4(link, forwardAnim, diff);
    } else {
        ActorSlot slot;
        slot.param = -1;
        slot.animation = forwardAnim;
        ActorObject_SetSecondarySlot_0208a724(context->scene->actorObjects[actorId], &slot, 0);
        slot.animation = backwardAnim;
        ActorObject_SetSecondarySlot_0208a724(context->scene->actorObjects[actorId], &slot, 1);
        func_ov001_0208a73c(context->scene->actorObjects[actorId], heading, data_ov001_020a0230, 0);
    }
    return 1;
}
