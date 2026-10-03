#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

extern TaggedValue *ResolveTaggedValueRef_020b0374(void *context, TaggedValue *value);
extern fx32 TaggedValueToFixed_020b03b0(TaggedValue *tagged);
extern BOOL Session_Exists_02063a24(void);
extern int func_ov001_02063a38(void);
extern void func_ov001_0209cc6c(u16 kind, u16 variant, VecFx32 *pos);
extern void AllocateListEntry_020bc6b0(VecFx32 *pos, u8 kind, u8 group, u8 extra);

int ScriptCmd_SpawnAtPosition_020b24ac(void *context, TaggedValue *operands)
{
    TaggedValue *kind;
    TaggedValue *variant;
    TaggedValue *x;
    TaggedValue *y;
    TaggedValue *z;
    VecFx32 pos;
    int mode;

    kind = ResolveTaggedValueRef_020b0374(context, operands);
    variant = ResolveTaggedValueRef_020b0374(context, operands + 1);
    x = ResolveTaggedValueRef_020b0374(context, operands + 2);
    y = ResolveTaggedValueRef_020b0374(context, operands + 3);
    z = ResolveTaggedValueRef_020b0374(context, operands + 4);
    pos.x = TaggedValueToFixed_020b03b0(x);
    pos.y = TaggedValueToFixed_020b03b0(y);
    pos.z = TaggedValueToFixed_020b03b0(z);
    if (Session_Exists_02063a24()) {
        mode = func_ov001_02063a38();
    } else {
        mode = 0;
    }
    switch (mode) {
    case 4:
        break;
    default:
        func_ov001_0209cc6c(kind->value, variant->value, &pos);
        break;
    case 7:
        if (kind->value == 1) {
            AllocateListEntry_020bc6b0(&pos, kind->value, 1, 0xff);
        } else {
            AllocateListEntry_020bc6b0(&pos, kind->value, 0xff, 0xff);
        }
        break;
    }
    return 0;
}