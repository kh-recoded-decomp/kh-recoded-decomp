#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x18c];
    fx32 stopDistanceSq;
    fx32 accel;
    fx32 maxSpeed;
    fx32 accelScale;
} PullDef;

typedef struct {
    u8 pad_00[0x18];
    VecFx32 position;
} PullTarget;

typedef struct {
    fx32 speed;
    PullDef *def;
    PullTarget *target;
    s32 state;
} PullWork;

typedef struct {
    u8 pad_00[0x10];
    s16 actorId;
} PullEvent;

typedef struct StageActor StageActor;

extern StageActor *GetStageActor_0209c040(int id);
extern VecFx32 *func_ov001_02090f04(StageActor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern int FixedPointMultiply12(int left, int right);
extern void ClearActorMotionState_02091194(StageActor *actor);
extern void ClearActorMotionSpeed_020911a8(StageActor *actor);
extern void AddObjectOffsetVector_02091c50(StageActor *actor, VecFx32 *offset);
extern void func_ov001_020958e4(PullEvent *event, int status);

BOOL PullActorTowardTarget_020d6644(PullEvent *event, PullWork *work)
{
    PullDef *def = work->def;
    PullTarget *target = work->target;
    StageActor *actor;
    VecFx32 pos;
    VecFx32 dir;

    switch (work->state) {
    default:
        work->state = 0;
    case 0:
        func_ov001_020958e4(event, 9);
        break;
    case 1:
        actor = GetStageActor_0209c040(event->actorId);
        pos = *func_ov001_02090f04(actor);
        VEC_Subtract_01ff9e3c(&target->position, &pos, &dir);
        if (VEC_DotProduct_01ff9e6c(&dir, &dir) > def->stopDistanceSq) {
            VEC_Normalize_01ff9f88(&dir, &dir);
            work->speed += FixedPointMultiply12(def->accel, def->accelScale);
            if (work->speed > def->maxSpeed) {
                work->speed = def->maxSpeed;
            }
            VEC_MultAdd_01ffa09c(work->speed, &dir, &pos, &pos);
            ClearActorMotionState_02091194(actor);
            ClearActorMotionSpeed_020911a8(actor);
            VEC_Subtract_01ff9e3c(&pos, func_ov001_02090f04(actor), &dir);
            AddObjectOffsetVector_02091c50(actor, &dir);
        } else {
            func_ov001_020958e4(event, 9);
            work->state = 0;
        }
        return TRUE;
    }
    return FALSE;
}
