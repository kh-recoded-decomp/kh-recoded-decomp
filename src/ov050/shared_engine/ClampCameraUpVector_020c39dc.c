#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct Basis {
    VecFx32 row[3];
} Basis;

typedef struct CameraOrient {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
} CameraOrient;

extern const s16 data_02053aac[];
extern void BuildBasisFromForward_0204bf70(const VecFx32 *forward, const VecFx32 *up, Basis *basis);
extern s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void RotateVectorAroundAxis_0204b34c(VecFx32 *vec, const VecFx32 *axis, s32 angle);

void ClampCameraUpVector_020c39dc(CameraOrient *camera)
{
    MtxFx33 rotation;
    VecFx32 target;
    MtxFx33 levelRotation;
    VecFx32 worldUp;
    Basis built;
    Basis basis;
    VecFx32 worldUpTmp;
    Basis levelBuilt;
    Basis levelBasis;
    fx32 limit;
    fx32 absY;
    s32 angle;
    s32 absAngle;
    s32 sign;
    s32 step;

    BuildBasisFromForward_0204bf70(&camera->direction, &camera->up, &built);
    basis = built;
    rotation = *(MtxFx33 *)&basis;
    camera->up = *(VecFx32 *)rotation.m[1];
    limit = data_02053aac[10];
    absY = camera->direction.y;
    if (absY < 0) {
        absY = -absY;
    }
    if (absY >= limit) {
        return;
    }
    worldUpTmp.x = 0;
    worldUpTmp.y = FX32_ONE;
    worldUpTmp.z = 0;
    worldUp = worldUpTmp;
    BuildBasisFromForward_0204bf70(&camera->direction, &worldUp, &levelBuilt);
    levelBasis = levelBuilt;
    levelRotation = *(MtxFx33 *)&levelBasis;
    target = *(VecFx32 *)levelRotation.m[1];
    angle = (s32)(((s64)AngleBetweenVecs_0204b070(&camera->up, &target) * 0x6488) / 0x10000);
    absAngle = angle < 0 ? -angle : angle;
    if (absAngle <= 0x595) {
        camera->up = target;
        return;
    }
    if (angle == 0) {
        sign = 0;
    } else if (angle > 0) {
        sign = 1;
    } else {
        sign = -1;
    }
    step = (s32)((s64)sign * 0x595);
    if (VEC_DotProduct_01ff9e6c(&target, (VecFx32 *)rotation.m[0]) < 0) {
        step = -step;
    }
    RotateVectorAroundAxis_0204b34c(&camera->up, &camera->direction, step);
}
