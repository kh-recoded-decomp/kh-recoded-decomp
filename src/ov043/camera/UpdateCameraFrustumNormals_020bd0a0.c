#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FrustumBasis {
    VecFx32 axes[3];
} FrustumBasis;

typedef struct FrustumProjection {
    fx32 sineHalfFov;
    fx32 cosineHalfFov;
} FrustumProjection;

typedef struct CameraFrustumState {
    fx32 sineHalfFov;
    fx32 cosineHalfFov;
    fx32 aspectRatio;
    u8 reserved00c[0xfc];
    VecFx32 leftNormal;
    VecFx32 rightNormal;
    VecFx32 topNormal;
    VecFx32 bottomNormal;
} CameraFrustumState;

extern CameraFrustumState *gOv043CameraState;
extern int NNS_G3dGlb_cameraMtx[];
extern void MTX_Copy43To33(const void *source, FrustumBasis *out);
extern int GetActiveCameraStateAddress(void);
extern fx16 FX_Atan2(fx32 y, fx32 x);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void RotateVecTowardVec(VecFx32 *vector, const VecFx32 *target, fx32 angle);
extern VecFx32 ReflectVectorAcrossNormal(const VecFx32 *vector, const VecFx32 *normal);
extern void ScaleVecFx32InPlace(VecFx32 *vector, fx32 scale);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *vector, VecFx32 *out);

static inline FrustumBasis GetFrustumBasis(void)
{
    FrustumBasis basis;
    MTX_Copy43To33(NNS_G3dGlb_cameraMtx, &basis);
    return basis;
}

static inline fx32 MultiplyFx32(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

static inline VecFx32 ScaledVector(const VecFx32 *vector, fx32 scale)
{
    VecFx32 result = *vector;
    ScaleVecFx32InPlace(&result, scale);
    return result;
}

static inline VecFx32 AddScaledVector(fx32 scale, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_MultAdd(scale, a, b, &result);
    return result;
}

static inline VecFx32 RotatedVector(const VecFx32 *vector, const VecFx32 *target, fx32 angle)
{
    VecFx32 result = *vector;
    RotateVecTowardVec(&result, target, angle);
    return result;
}

void UpdateCameraFrustumNormals_020bd0a0(void)
{
    CameraFrustumState *camera = gOv043CameraState;
    CameraFrustumState *normals;
    FrustumBasis basis = GetFrustumBasis();
    const FrustumProjection *active = (const FrustumProjection *)GetActiveCameraStateAddress();
    fx32 angle = FX_Atan2(active->sineHalfFov, active->cosineHalfFov);

    camera->topNormal = RotatedVector(&basis.axes[1], &basis.axes[2], angle);
    camera->bottomNormal = ReflectVectorAcrossNormal(&(normals = camera)->topNormal, &basis.axes[2]);
    normals->rightNormal = ScaledVector(&basis.axes[0],
        MultiplyFx32(normals->cosineHalfFov, FX_Div(0x1000, normals->aspectRatio)));
    normals->rightNormal = AddScaledVector(camera->sineHalfFov, &basis.axes[2], &normals->rightNormal);
    VEC_Normalize(&normals->rightNormal, &camera->rightNormal);
    camera->leftNormal = ReflectVectorAcrossNormal(&normals->rightNormal, &basis.axes[2]);
}
