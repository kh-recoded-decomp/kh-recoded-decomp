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

extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern fx32 TaggedValueToFixed_020b03b0(TaggedValue *tagged);
extern int nextRandom12_0202aa58(void);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

int ScriptCmd_PushRandomHorizontal_020b15e8(ScriptContext *context, u8 *args)
{
    TaggedValue *minRef;
    fx32 range;
    fx32 minDist;
    VecFx32 dir;

    minRef = ResolveTaggedValueRef_020b0374(context, (TaggedValue *)(args + 8));
    range = TaggedValueToFixed_020b03b0(ResolveTaggedValueRef_020b0374(context, (TaggedValue *)(args + 0x10)));
    range -= TaggedValueToFixed_020b03b0(minRef);
    dir.x = nextRandom12_0202aa58() - 0x800;
    dir.y = 0;
    dir.z = nextRandom12_0202aa58() - 0x800;
    if (VEC_Mag_01ff9f28(&dir) == 0) {
        dir.z = 0x1000;
    }
    func_01ffaff4(&dir, &dir);
    minDist = TaggedValueToFixed_020b03b0(minRef);
    VEC_MultAdd_01ffa09c(minDist + FixedPointMultiply12(range, nextRandom12_0202aa58()), &dir, &context->position, &context->position);
    return 0;
}
