#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraShot {
    VecFx32 position;
    VecFx32 direction;
    u8 pad18[0x10];
    VecFx32 normal;
    s32 usesFocus;
    fx32 positionBlend;
    fx32 rotationBlend;
    s32 normalized : 1;
    s32 dirty : 1;
    s32 arc : 1;
} CameraShot;

typedef struct EventCameraWork {
    CameraShot current;
    CameraShot start;
    CameraShot end;
    CameraShot source;
    s32 mode;
    s32 timer;
    s32 duration;
    u8 pad11c[0xc];
    u8 matrix[0x30];
} EventCameraWork;

extern void func_ov046_020c2d8c(void *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *in, VecFx32 *out);
extern void ComputeEventCameraArcAngle_020c4260(EventCameraWork *work);

void SetupEventCameraShot_020c4510(EventCameraWork *work, const CameraShot *start, const CameraShot *end, s32 mode, s32 duration)
{
    work->source = *end;
    work->start = *start;
    work->current = work->start;
    work->end = *end;
    work->current.arc = work->end.arc;
    work->current.positionBlend = work->end.positionBlend;
    work->current.rotationBlend = work->end.rotationBlend;
    if (work->start.usesFocus != 0 || work->end.usesFocus != 0) {
        func_ov046_020c2d8c(work->matrix);
    }
    if (work->end.normalized) {
        work->current.normalized = 1;
    }
    if (work->current.normalized) {
        if (!work->start.normalized) {
            VecFx32 dir;
            VecFx32 delta;
            VecFx32 deltaArg;
            VEC_Subtract_01ff9e3c(&work->start.direction, &work->start.position, &delta);
            deltaArg = delta;
            func_01ff9f88(&deltaArg, &dir);
            work->start.direction = dir;
            work->start.normalized = 1;
            work->start.dirty = 0;
        }
        if (!work->end.normalized) {
            VecFx32 dir;
            VecFx32 delta;
            VecFx32 deltaArg;
            VEC_Subtract_01ff9e3c(&work->end.direction, &work->end.position, &delta);
            deltaArg = delta;
            func_01ff9f88(&deltaArg, &dir);
            work->end.direction = dir;
            work->end.normalized = 1;
            work->end.dirty = 0;
        }
        work->current.dirty = 0;
    } else {
        work->current.dirty = end->dirty;
        if (work->current.dirty) {
            work->current.normal = work->end.normal;
            ComputeEventCameraArcAngle_020c4260(work);
        }
    }
    work->mode = mode;
    work->duration = duration;
    work->timer = 0;
}
