#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 data[0xd4];
} HitResult;

typedef struct {
    u8 pad_00[0x18];
    fx32 maxDistance;
    s32 duration;
} EffectParams;

typedef struct {
    u8 pad_00[2];
    s8 state;
    u8 pad_03;
    s32 timer;
    u8 pad_08[0x10];
    VecFx32 origin;
    u8 pad_24[0xb0];
    VecFx32 position;
    u8 pad_e0[0x58];
    EffectParams *params;
} EffectObj;

extern VecFx32 func_ov021_020ab1f0(void *context, EffectObj *obj, int delta);
extern HitResult func_ov021_020ab0c8(void *context, EffectObj *obj, VecFx32 *position, const VecFx32 *velocity);
extern BOOL func_ov021_020ab41c(EffectObj *obj, int delta);
extern void AdvanceToSecondPhase_020ab5f0(EffectObj *obj);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

BOOL UpdateEffectMovePhase_020ab4ac(void *context, EffectObj *obj, int delta)
{
    EffectParams *params = obj->params;
    VecFx32 position;
    VecFx32 velocity;
    BOOL finished;
    BOOL hit;

    obj->timer += delta;
    position = obj->position;
    velocity = func_ov021_020ab1f0(context, obj, delta);
    func_ov021_020ab0c8(context, obj, &position, &velocity);
    VEC_Add_01ff9e0c(&position, &velocity, &position);
    obj->position = position;
    if (obj->state == 1) {
        finished = FALSE;
        hit = func_ov021_020ab41c(obj, delta);
        if (params->duration >= 0) {
            if (obj->timer >= params->duration) {
                finished = TRUE;
            }
        } else if (hit) {
            finished = TRUE;
        }
        if (params->maxDistance >= 0 && func_01ffa0f4(&obj->origin, &position) > params->maxDistance) {
            finished = TRUE;
        }
        if (finished) {
            AdvanceToSecondPhase_020ab5f0(obj);
        }
    }
    return obj->state == -1;
}
