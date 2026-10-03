#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageMarker {
    u32 flags;
    VecFx32 position;
    fx32 radius;
    u8 pad14[0xc];
} StageMarker;

typedef struct StageManager {
    u8 pad0[0x18e78];
    StageMarker markers[1];
} StageManager;

typedef struct TaggedValue {
    s16 tag;
    s16 pad2;
    int value;
} TaggedValue;

typedef struct MarkerOperands {
    u8 index[8];
    u8 pad8[4];
    u32 flags;
    u8 position[0x18];
    u8 radius[8];
} MarkerOperands;

extern TaggedValue *ResolveTaggedValueRef_020b0374(void *context, void *value);
extern s32 TaggedValueToFixed_020b03b0(void *tagged);
extern StageManager *func_ov001_0209c3c0(void);
extern void func_ov021_020b0508(void *context, u32 flags, void *operands, VecFx32 *out, int *extra);

int ScriptOp_SetStageMarker_020b2f58(void *context, MarkerOperands *operands)
{
    TaggedValue *index = ResolveTaggedValueRef_020b0374(context, operands->index);
    void *radius = ResolveTaggedValueRef_020b0374(context, operands->radius);
    int extra = 0;
    StageManager *stage = func_ov001_0209c3c0();
    VecFx32 position;

    func_ov021_020b0508(context, operands->flags & ~0x40, operands->position, &position, &extra);
    stage->markers[index->value].flags = operands->flags;
    stage->markers[index->value].position = position;
    stage->markers[index->value].radius = TaggedValueToFixed_020b03b0(radius);
    return 0;
}
