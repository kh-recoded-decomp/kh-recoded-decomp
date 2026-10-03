#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventCameraWork {
    u8 pad000[0x28];
    VecFx32 normal;
    u8 pad034[0x10];
    VecFx32 start;
    u8 pad050[0x38];
    VecFx32 end;
    VecFx32 center;
    u8 pad0a0[0x7c];
    s32 arcAngle;
} EventCameraWork;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_0204aea8(VecFx32 *out, const VecFx32 *vec, const VecFx32 *normal);
extern s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

void ComputeEventCameraArcAngle_020c4260(EventCameraWork *work)
{
    VecFx32 toStart;
    VecFx32 toEnd;
    VecFx32 flatStart;
    VecFx32 flatEnd;
    VecFx32 cross;
    VecFx32 flatStartTmp;
    VecFx32 flatEndTmp;
    VecFx32 toStartTmp;
    VecFx32 toEndTmp;
    VecFx32 crossTmp;
    s32 angle;

    VEC_Subtract_01ff9e3c(&work->start, &work->center, &toStartTmp);
    toStart = toStartTmp;
    VEC_Subtract_01ff9e3c(&work->end, &work->center, &toEndTmp);
    toEnd = toEndTmp;
    func_0204aea8(&flatStartTmp, &toStart, &work->normal);
    flatStart = flatStartTmp;
    func_0204aea8(&flatEndTmp, &toEnd, &work->normal);
    flatEnd = flatEndTmp;
    angle = AngleBetweenVecs_0204b070(&flatStart, &flatEnd);
    work->arcAngle = (s32)(((s64)angle * 0x6488) / 0x10000);
    VEC_CrossProduct_01ff9ea8(&flatStart, &work->normal, &crossTmp);
    cross = crossTmp;
    if (VEC_DotProduct_01ff9e6c(&cross, &flatEnd) < 0) {
        work->arcAngle = -work->arcAngle;
    }
}
