#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x2c];
    TaggedValue result;
} ScriptContext;

extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt_020b0398(TaggedValue *tagged);
extern s32 TaggedValueToFixed_020b03b0(TaggedValue *tagged);

s32 ScriptOp_SubtractValues_020b2be4(ScriptContext *context, TaggedValue *operands)
{
    TaggedValue *left = ResolveTaggedValueRef_020b0374(context, operands);
    TaggedValue *right = ResolveTaggedValueRef_020b0374(context, operands + 1);
    s32 leftValue;
    s32 rightValue;
    s32 tag = left->tag;

    if (tag == 1) {
        context->result.tag = 1;
        leftValue = TaggedValueToInt_020b0398(left);
        rightValue = TaggedValueToInt_020b0398(right);
    } else if (tag == 0x10) {
        context->result.tag = 0x10;
        leftValue = TaggedValueToFixed_020b03b0(left);
        rightValue = TaggedValueToFixed_020b03b0(right);
    } else {
        goto done;
    }
    context->result.value = leftValue - rightValue;
done:
    return 0;
}
