#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[4];
    u16 stateFlags;
    u16 eventFlags;
} StageActor;

typedef struct {
    u8 pad_00[0x1d0];
    u16 mode;
} StageTarget;

typedef struct {
    StageActor *actor;
    u32 pad_04;
    StageTarget *target;
} StageGlobals;

typedef struct {
    u8 pad_00[0x9c];
    u32 firedEvents : 31;
    u32 locked : 1;
} ScriptContext;

extern StageGlobals data_ov021_020b56a4;
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern void ClearWalkerStepState_02091964(StageTarget *target);

int ScriptCmd_TriggerActorEvent_020b2a4c(ScriptContext *context, TaggedValue *operand)
{
    int event = ResolveTaggedValueRef_020b0374(context, operand)->value;
    StageActor *actor = data_ov021_020b56a4.actor;
    StageTarget *target = data_ov021_020b56a4.target;

    if (target->mode == 1 && actor != NULL) {
        switch (event) {
        case 0xc:
            actor->stateFlags |= 1 << 14;
            break;
        case 0x10:
            actor->stateFlags |= 2 << 14;
            break;
        case 0x11:
            actor->eventFlags = (actor->eventFlags & ~1) | 1;
            break;
        case 9:
            actor->eventFlags |= 2;
            break;
        }
    }
    if (target != NULL && event == 9) {
        ClearWalkerStepState_02091964(target);
    }
    context->firedEvents |= 1 << event;
    return 0;
}
