#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x18e60];
    VecFx32 points[2];
} StageState;

extern TaggedValue *ResolveTaggedValueRef_020b0374(void *context, TaggedValue *value);
extern fx32 TaggedValueToFixed_020b03b0(TaggedValue *tagged);
extern StageState *func_ov001_0209c3c0(void);

int ScriptCmd_SetStagePoint_020b2050(void *context, TaggedValue *operands)
{
    TaggedValue *slot;
    TaggedValue *x;
    TaggedValue *y;
    TaggedValue *z;
    StageState *stage;

    slot = ResolveTaggedValueRef_020b0374(context, operands);
    x = ResolveTaggedValueRef_020b0374(context, operands + 1);
    y = ResolveTaggedValueRef_020b0374(context, operands + 2);
    z = ResolveTaggedValueRef_020b0374(context, operands + 3);
    stage = func_ov001_0209c3c0();
    if (slot->value < 0 || slot->value > 1) {
        return 0;
    }
    stage->points[slot->value].x = TaggedValueToFixed_020b03b0(x);
    stage->points[slot->value].y = TaggedValueToFixed_020b03b0(y);
    stage->points[slot->value].z = TaggedValueToFixed_020b03b0(z);
    return 0;
}
