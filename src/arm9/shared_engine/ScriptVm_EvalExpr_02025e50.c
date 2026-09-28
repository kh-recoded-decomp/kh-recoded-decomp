#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptValue {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptValue;

typedef struct ScriptContext {
    u8 pad_000[0x218];
    ScriptValue stack[1];
} ScriptContext;

#define SCRIPT_FIXED 0x10
#define SCRIPT_INT 1

extern void func_01ff869c(const void *src, void *dest, u32 size);
extern ScriptValue *ScriptVm_ResolveOperand_02025d08(ScriptContext *ctx, u16 *operand);
extern fx32 func_02025e28(ScriptValue *value);
extern s32 GetField4UnlessState2_02025e40(ScriptValue *value);
extern fx32 FixedPointMultiply12(fx32 left, fx32 right);
extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern s32 func_02023dbc(s32 numerator, s32 denominator);

#define BINARY_CMP(OP)                                                   \
    {                                                                    \
        ScriptValue *right = &ctx->stack[depth - 1];                     \
        ScriptValue *left = &ctx->stack[depth - 2];                      \
                                                                         \
        if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) { \
            fx32 x = func_02025e28(left);                                \
                                                                         \
            left->value = (x OP func_02025e28(right)) ? 1 : 0;           \
            left->type = SCRIPT_INT;                                     \
        } else {                                                         \
            s32 x = GetField4UnlessState2_02025e40(left);                \
                                                                         \
            left->value = (x OP GetField4UnlessState2_02025e40(right)) ? 1 : 0; \
            left->type = SCRIPT_INT;                                     \
        }                                                                \
        depth--;                                                         \
    }

ScriptValue *ScriptVm_EvalExpr_02025e50(ScriptContext *ctx, u16 *code)
{
    int depth = 0;

    while (*code != 0xf) {
        switch (*(volatile u16 *)code) {
        case 0: {
            u16 operand[4];

            func_01ff869c(code + 1, operand, sizeof(operand));
            ctx->stack[depth] = *ScriptVm_ResolveOperand_02025d08(ctx, operand);
            depth++;
            code += 4;
            break;
        }
        case 1: {
            ScriptValue *top = &ctx->stack[depth - 1];

            top->value = -top->value;
            break;
        }
        case 2: {
            ScriptValue *top = &ctx->stack[depth - 1];

            top->value = top->value == 0 ? 1 : 0;
            break;
        }
        case 3: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) {
                fx32 x = func_02025e28(left);

                /* Shipped code adds the left operand to itself. */
                left->value = x + func_02025e28(left);
                left->type = SCRIPT_FIXED;
            } else {
                s32 x = GetField4UnlessState2_02025e40(left);

                left->value = x + GetField4UnlessState2_02025e40(right);
                left->type = SCRIPT_INT;
            }
            depth--;
            break;
        }
        case 4: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) {
                fx32 x = func_02025e28(left);

                left->value = x - func_02025e28(right);
                left->type = SCRIPT_FIXED;
            } else {
                s32 x = GetField4UnlessState2_02025e40(left);

                left->value = x - GetField4UnlessState2_02025e40(right);
                left->type = SCRIPT_INT;
            }
            depth--;
            break;
        }
        case 5: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) {
                fx32 x = func_02025e28(left);

                left->value = FixedPointMultiply12(x, func_02025e28(right));
                left->type = SCRIPT_FIXED;
            } else {
                s32 x = GetField4UnlessState2_02025e40(left);

                left->value = x * GetField4UnlessState2_02025e40(right);
                left->type = SCRIPT_INT;
            }
            depth--;
            break;
        }
        case 6: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) {
                fx32 x = func_02025e28(left);

                left->value = FX_Div_01ff9c84(x, func_02025e28(right));
                left->type = SCRIPT_FIXED;
            } else {
                s32 x = GetField4UnlessState2_02025e40(left);

                left->value = func_02023dbc(x, GetField4UnlessState2_02025e40(right));
                left->type = SCRIPT_INT;
            }
            depth--;
            break;
        }
        case 7:
            BINARY_CMP(==)
            break;
        case 8:
            BINARY_CMP(>)
            break;
        case 9:
            BINARY_CMP(<)
            break;
        case 10:
            BINARY_CMP(>=)
            break;
        case 11:
            BINARY_CMP(<=)
            break;
        case 12:
            BINARY_CMP(!=)
            break;
        case 13: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            left->value = (left->value != 0 && right->value != 0) ? 1 : 0;
            depth--;
            break;
        }
        case 14: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            left->value = (left->value != 0 || right->value != 0) ? 1 : 0;
            depth--;
            break;
        }
        }
        code++;
    }
    return &ctx->stack[depth - 1];
}
