#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageManager {
    u8 pad0[0x18e50];
    VecFx32 offset;
} StageManager;

extern void *ResolveTaggedValueRef_020b0374(void *context, void *value);
extern s32 TaggedValueToFixed_020b03b0(void *tagged);
extern StageManager *func_ov001_0209c3c0(void);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

int ScriptOp_AddStageOffset_020b2450(void *context, u8 *operands)
{
    VecFx32 delta;
    void *tagX = ResolveTaggedValueRef_020b0374(context, operands);
    void *tagY = ResolveTaggedValueRef_020b0374(context, operands + 8);
    void *tagZ = ResolveTaggedValueRef_020b0374(context, operands + 0x10);
    StageManager *stage = func_ov001_0209c3c0();

    delta.x = TaggedValueToFixed_020b03b0(tagX);
    delta.y = TaggedValueToFixed_020b03b0(tagY);
    delta.z = TaggedValueToFixed_020b03b0(tagZ);
    VEC_Add_01ff9e0c(&delta, &stage->offset, &stage->offset);
    return 0;
}
