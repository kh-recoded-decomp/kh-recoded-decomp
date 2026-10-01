#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef s32 (*ScriptHandler)(void *context, TaggedValue *operands);

extern TaggedValue *ResolveTaggedValueRef_020b0374(void *context, TaggedValue *value);
extern ScriptHandler data_ov021_020b52b4[];

s32 DispatchScriptHandler_020b34b0(void *context, TaggedValue *operands)
{
    TaggedValue *selector;
    ScriptHandler handler;

    selector = ResolveTaggedValueRef_020b0374(context, operands);
    handler = data_ov021_020b52b4[selector->value];
    if (handler != NULL) {
        handler(context, operands);
    }
    return 0;
}
