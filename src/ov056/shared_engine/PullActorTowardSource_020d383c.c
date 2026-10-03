#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PullSource {
    u8 pad_000[0xf4];
    VecFx32 position;
    fx32 strength;
} PullSource;

typedef struct PullWork {
    fx32 speed;
    PullSource *source;
    s32 state;
} PullWork;

typedef struct PullEvent {
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

BOOL PullActorTowardSource_020d383c(PullEvent *event, PullWork *work)
{
    PullSource *source;
    StageActor *actor;
    fx32 step;
    fx32 speed;
    VecFx32 pos;
    VecFx32 dir;

    switch (work->state) {
    default:
        work->state = 0;
    case 0:
        func_ov001_020958e4(event, 9);
        break;
    case 1:
        source = work->source;
        actor = GetStageActor_0209c040(event->actorId);
        step = FixedPointMultiply12(0xb2, source->strength);
        pos = *func_ov001_02090f04(actor);
        VEC_Subtract_01ff9e3c(&source->position, &pos, &dir);
        if (VEC_DotProduct_01ff9e6c(&dir, &dir) > FixedPointMultiply12(0xccd, 0xccd)) {
            VEC_Normalize_01ff9f88(&dir, &dir);
            speed = work->speed + step;
            if (speed >= 0xc00) {
                speed = 0xc00;
            }
            work->speed = speed;
            VEC_MultAdd_01ffa09c(speed, &dir, &pos, &pos);
            ClearActorMotionState_02091194(actor);
            ClearActorMotionSpeed_020911a8(actor);
            VEC_Subtract_01ff9e3c(&pos, func_ov001_02090f04(actor), &dir);
            AddObjectOffsetVector_02091c50(actor, &dir);
        }
        return TRUE;
    }
    return FALSE;
}
