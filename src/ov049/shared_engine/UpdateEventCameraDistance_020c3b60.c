#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventCameraWork {
    VecFx32 position;
    u8 pad00c[0x190];
    fx32 distance;
    fx32 targetDistance;
} EventCameraWork;

extern void func_ov046_020c2cb8(VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *in, VecFx32 *out);
extern void VEC_MultAdd_01ffa09c(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern int FixedPointMultiply12(int left, int right);
extern void func_ov049_020c3fd0(EventCameraWork *work);

void UpdateEventCameraDistance_020c3b60(EventCameraWork *work)
{
    VecFx32 target;
    VecFx32 focus;
    VecFx32 dirArg;
    VecFx32 dir;
    VecFx32 delta;
    VecFx32 deltaArg;
    fx32 goal;
    fx32 diff;
    fx32 absDiff;
    s32 sign;

    func_ov046_020c2cb8(&focus);
    target = focus;
    goal = work->targetDistance;
    if (work->distance != goal) {
        diff = goal - work->distance;
        if (diff < 0) {
            absDiff = -diff;
        } else {
            absDiff = diff;
        }
        if (absDiff < 0x10) {
            work->distance = goal;
        } else {
            sign = diff >= 0 ? 1 : -1;
            diff = FixedPointMultiply12(diff, 0x4cd);
            work->distance += diff + sign * 0x10;
        }
    }
    VEC_Subtract_01ff9e3c(&work->position, &target, &delta);
    deltaArg = delta;
    func_01ff9f88(&deltaArg, &dir);
    dirArg = dir;
    VEC_MultAdd_01ffa09c(work->distance, &dirArg, &target, &work->position);
    func_ov049_020c3fd0(work);
}
