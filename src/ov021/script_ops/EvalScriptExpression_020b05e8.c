#include "nitro/types.h"

typedef struct TaggedValue {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct ScriptContext {
    u8 pad_00[0x40];
    TaggedValue stack[1];
} ScriptContext;

#define TAG_FIXED 0x10
#define TAG_INT 1

extern void MIi_CpuCopy16_01ff869c(const void *source, void *dest, u32 size);
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt_020b0398(TaggedValue *tagged);
extern s32 TaggedValueToFixed_020b03b0(TaggedValue *tagged);
extern int FixedPointMultiply12(int left, int right);
extern int FX_Div_01ff9c84(int numer, int denom);

#define COMPARE(OP)                                              \
    {                                                            \
        TaggedValue *rhs = &context->stack[depth - 1];           \
        TaggedValue *lhs = &context->stack[depth - 2];           \
        if ((lhs->tag & TAG_FIXED) || (rhs->tag & TAG_FIXED)) {  \
            s32 left = TaggedValueToFixed_020b03b0(lhs);         \
            s32 right = TaggedValueToFixed_020b03b0(rhs);        \
            lhs->value = left OP right;                          \
            lhs->tag = TAG_INT;                                  \
        } else {                                                 \
            s32 left = TaggedValueToInt_020b0398(lhs);           \
            s32 right = TaggedValueToInt_020b0398(rhs);          \
            lhs->value = left OP right;                          \
            lhs->tag = TAG_INT;                                  \
        }                                                        \
        depth--;                                                 \
        break;                                                   \
    }

TaggedValue *EvalScriptExpression_020b05e8(ScriptContext *context, u16 *code)
{
    int depth = 0;

    while (*code != 0xf) {
        switch (*(volatile u16 *)code) {
        case 0: {
            TaggedValue operand;
            MIi_CpuCopy16_01ff869c(code + 1, &operand, sizeof(operand));
            context->stack[depth] = *ResolveTaggedValueRef_020b0374(context, &operand);
            depth++;
            code += 4;
            break;
        }
        case 1: {
            TaggedValue *top = &context->stack[depth - 1];
            top->value = -top->value;
            break;
        }
        case 2: {
            TaggedValue *top = &context->stack[depth - 1];
            top->value = top->value == 0 ? 1 : 0;
            break;
        }
        case 3: {
            TaggedValue *rhs = &context->stack[depth - 1];
            TaggedValue *lhs = &context->stack[depth - 2];
            if (lhs->tag == TAG_FIXED || rhs->tag == TAG_FIXED) {
                s32 left = TaggedValueToFixed_020b03b0(lhs);
                lhs->value = left + TaggedValueToFixed_020b03b0(lhs);
                lhs->tag = TAG_FIXED;
            } else {
                s32 left = TaggedValueToInt_020b0398(lhs);
                lhs->value = left + TaggedValueToInt_020b0398(rhs);
                lhs->tag = TAG_INT;
            }
            depth--;
            break;
        }
        case 4: {
            TaggedValue *rhs = &context->stack[depth - 1];
            TaggedValue *lhs = &context->stack[depth - 2];
            if (lhs->tag == TAG_FIXED || rhs->tag == TAG_FIXED) {
                s32 left = TaggedValueToFixed_020b03b0(lhs);
                lhs->value = left - TaggedValueToFixed_020b03b0(rhs);
                lhs->tag = TAG_FIXED;
            } else {
                s32 left = TaggedValueToInt_020b0398(lhs);
                lhs->value = left - TaggedValueToInt_020b0398(rhs);
                lhs->tag = TAG_INT;
            }
            depth--;
            break;
        }
        case 5: {
            TaggedValue *rhs = &context->stack[depth - 1];
            TaggedValue *lhs = &context->stack[depth - 2];
            if (lhs->tag == TAG_FIXED || rhs->tag == TAG_FIXED) {
                s32 left = TaggedValueToFixed_020b03b0(lhs);
                lhs->value = FixedPointMultiply12(left, TaggedValueToFixed_020b03b0(rhs));
                lhs->tag = TAG_FIXED;
            } else {
                s32 left = TaggedValueToInt_020b0398(lhs);
                lhs->value = left * TaggedValueToInt_020b0398(rhs);
                lhs->tag = TAG_INT;
            }
            depth--;
            break;
        }
        case 6: {
            TaggedValue *rhs = &context->stack[depth - 1];
            TaggedValue *lhs = &context->stack[depth - 2];
            if (lhs->tag == TAG_FIXED || rhs->tag == TAG_FIXED) {
                s32 left = TaggedValueToFixed_020b03b0(lhs);
                lhs->value = FX_Div_01ff9c84(left, TaggedValueToFixed_020b03b0(rhs));
                lhs->tag = TAG_FIXED;
            } else {
                s32 left = TaggedValueToInt_020b0398(lhs);
                lhs->value = left / TaggedValueToInt_020b0398(rhs);
                lhs->tag = TAG_INT;
            }
            depth--;
            break;
        }
        case 7:
            COMPARE(==)
        case 8:
            COMPARE(>)
        case 9:
            COMPARE(<)
        case 10:
            COMPARE(>=)
        case 11:
            COMPARE(<=)
        case 12:
            COMPARE(!=)
        case 13: {
            TaggedValue *rhs = &context->stack[depth - 1];
            TaggedValue *lhs = &context->stack[depth - 2];
            lhs->value = (lhs->value != 0 && rhs->value != 0) ? 1 : 0;
            depth--;
            break;
        }
        case 14: {
            TaggedValue *rhs = &context->stack[depth - 1];
            TaggedValue *lhs = &context->stack[depth - 2];
            lhs->value = (lhs->value != 0 || rhs->value != 0) ? 1 : 0;
            depth--;
            break;
        }
        }
        code++;
    }
    return &context->stack[depth - 1];
}
