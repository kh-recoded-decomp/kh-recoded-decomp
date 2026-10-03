#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} ScriptContext;

typedef struct {
    void *actor;
    u32 pad_04;
    void *target;
} StageGlobals;

extern StageGlobals data_ov021_020b56a4;
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern fx32 TaggedValueToFixed_020b03b0(TaggedValue *tagged);
extern void func_ov001_02091c34(void *target, VecFx32 *out);
extern VecFx32 *func_ov001_02090f04(void *target);

void ResolveVectorOperand_020b03c8(ScriptContext *context, TaggedValue *operand, VecFx32 *out)
{
    TaggedValue *x;
    TaggedValue *y;
    TaggedValue *z;

    switch (operand->value) {
    case -1:
        func_ov001_02091c34(data_ov021_020b56a4.target, out);
        return;
    case -2:
        *out = *func_ov001_02090f04(data_ov021_020b56a4.target);
        return;
    case -10:
        *out = context->position;
        return;
    }
    x = ResolveTaggedValueRef_020b0374(context, operand);
    y = ResolveTaggedValueRef_020b0374(context, operand + 1);
    z = ResolveTaggedValueRef_020b0374(context, operand + 2);
    out->x = TaggedValueToFixed_020b03b0(x);
    out->y = TaggedValueToFixed_020b03b0(y);
    out->z = TaggedValueToFixed_020b03b0(z);
}
