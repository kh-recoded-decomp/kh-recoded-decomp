#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 data[0xd4];
} HitResult;

typedef struct {
    u8 pad_00[2];
    s8 state;
    u8 pad_03;
    s32 timer;
    u8 pad_08[0x28];
    u8 animation[0xa4];
    VecFx32 position;
} EffectObj;

extern const VecFx32 data_02053438;

extern int func_0202f4b8(void *animation, u16 index);
extern HitResult func_ov021_020ab0c8(void *context, EffectObj *obj, VecFx32 *position, const VecFx32 *velocity);
extern BOOL func_ov021_020ab41c(EffectObj *obj, int delta);

BOOL UpdateEffectAnimationPhase_020ab564(void *context, EffectObj *obj, int delta)
{
    VecFx32 position = obj->position;
    VecFx32 velocity = data_02053438;
    int i;
    int duration;

    for (i = 0; i < 5; i++) {
        duration = func_0202f4b8(obj->animation, i);
        if (duration > 0) {
            break;
        }
    }
    obj->timer += delta;
    if (obj->timer <= duration - 0x9000) {
        func_ov021_020ab0c8(context, obj, &position, &velocity);
    }
    if (func_ov021_020ab41c(obj, delta)) {
        obj->state = -1;
    }
    return obj->state == -1;
}
