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

extern VecFx32 data_02053438;
extern const s16 data_0205372c[];
extern void CopyAnimTransform_020c4228(const void *src, CameraShot *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL AreVecsWithinRange16_0204a8f4(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9f88(const VecFx32 *in, VecFx32 *out);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ComputeEventCameraArcAngle_020c4260(EventCameraWork *work);

void InitEventCameraShot_020c4330(EventCameraWork *work, const void *startSrc, const void *endSrc, s32 mode, s32 duration)
{
    VecFx32 axis;
    VecFx32 offset;
    VecFx32 crossTmp;
    VecFx32 offsetTmp;
    VecFx32 scaled;
    VecFx32 up;
    fx32 limit;
    fx32 absY;
    fx32 projection;

    CopyAnimTransform_020c4228(startSrc, &work->start);
    CopyAnimTransform_020c4228(endSrc, &work->end);
    work->current = work->start;
    work->mode = mode;
    work->duration = duration;
    work->timer = 0;
    if (VEC_DotProduct_01ff9e6c(&work->start.direction, &work->end.direction) >= 0) {
        return;
    }
    VEC_CrossProduct_01ff9ea8(&work->start.direction, &work->end.direction, &crossTmp);
    axis = crossTmp;
    if (AreVecsWithinRange16_0204a8f4(&axis, &data_02053438)) {
        return;
    }
    func_01ff9f88(&axis, &axis);
    limit = data_0205372c[3];
    absY = axis.y;
    if (absY < 0) {
        absY = -absY;
    }
    if (absY > limit) {
        return;
    }
    if (work->end.normalized) {
        work->end.direction = *func_ov001_0206dc4c(0);
        work->current.direction = work->end.direction;
        work->end.normalized = 0;
        work->current.normalized = work->end.normalized;
        if (work->start.normalized) {
            VEC_Subtract_01ff9e3c(&work->end.direction, &work->start.position, &offsetTmp);
            offset = offsetTmp;
            projection = VEC_DotProduct_01ff9e6c(&offset, &work->start.direction);
            scaled = work->start.direction;
            ScaleVecFx32InPlace_0204a5e4(&scaled, projection);
            work->start.direction = scaled;
            VEC_Add_01ff9e0c(&work->start.direction, &work->start.position, &work->start.direction);
            work->start.normalized = 0;
        }
    }
    work->start.dirty = 1;
    work->end.dirty = work->start.dirty;
    work->current.dirty = work->end.dirty;
    up.x = 0;
    up.y = 0x1000;
    up.z = 0;
    work->start.normal = up;
    work->end.normal = work->start.normal;
    work->current.normal = work->end.normal;
    ComputeEventCameraArcAngle_020c4260(work);
}
