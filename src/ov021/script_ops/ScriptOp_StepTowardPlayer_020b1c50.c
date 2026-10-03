#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptContext {
    u8 pad0[0x34];
    VecFx32 position;
} ScriptContext;

typedef struct ActiveContext {
    void *stage;
    int pad4;
    void *object;
} ActiveContext;

extern ActiveContext data_ov021_020b56a4;
extern void *ResolveTaggedValueRef_020b0374(ScriptContext *context, void *value);
extern s32 TaggedValueToFixed_020b03b0(void *tagged);
extern void func_ov001_02091c34(void *object, VecFx32 *pos);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

int ScriptOp_StepTowardPlayer_020b1c50(ScriptContext *context, u8 *operands)
{
    VecFx32 origin;
    VecFx32 target;
    VecFx32 delta;
    VecFx32 direction;
    void *tagged = ResolveTaggedValueRef_020b0374(context, operands + 8);

    origin = context->position;
    func_ov001_02091c34(data_ov021_020b56a4.object, &target);
    VEC_Subtract_01ff9e3c(&target, &origin, &delta);
    VEC_Normalize_01ff9f88(&delta, &direction);
    VEC_MultAdd_01ffa09c(TaggedValueToFixed_020b03b0(tagged), &direction, &target, &context->position);
    return 0;
}
