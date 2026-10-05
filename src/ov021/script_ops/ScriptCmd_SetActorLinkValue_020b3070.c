#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_000[0x288];
    u16 lowBits : 8;
    u16 hasLink : 1;
    u16 highBits : 7;
    u8 pad_28a[0x2ac - 0x28a];
    s32 linkValue;
} StageActor;

extern TaggedValue *ResolveTaggedValueRef_020b0374(void *context, TaggedValue *value);
extern StageActor *ResolveStageActorRef_020b02b8(void *context, s32 id);

int ScriptCmd_SetActorLinkValue_020b3070(void *context, TaggedValue *operands)
{
    TaggedValue *actorRef = ResolveTaggedValueRef_020b0374(context, operands);
    TaggedValue *linkRef = ResolveTaggedValueRef_020b0374(context, operands + 1);
    StageActor *actor;
    ResolveTaggedValueRef_020b0374(context, operands + 2);
    actor = ResolveStageActorRef_020b02b8(context, actorRef->value);
    if (actor != NULL) {
        actor->linkValue = linkRef->value;
        actor->hasLink = (linkRef->value != 0);
        return 0;
    }
    return 0;
}
