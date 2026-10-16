#include "src/overlays/ov042/Ov042CameraState.h"

#define FX32_PI 0x3244

typedef struct CameraMatrix33 { VecFx32 rows[3]; } CameraMatrix33;
typedef struct CameraMatrix43 { VecFx32 rows[4]; } CameraMatrix43;

extern CameraMatrix43 NNS_G3dGlb_cameraMtx;
extern const fx16 gSinFx12Table[4096];
extern fx32 VEC_Mag(const VecFx32 *vector);
extern void MTX_Copy43To33(const CameraMatrix43 *source, CameraMatrix33 *destination);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void ScaleVecFx32InPlace(VecFx32 *vector, fx32 scale);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *result);

void SetCameraColliderOffsetAngle(fx32 degrees)
{
    CameraMatrix33 basis;
    CameraMatrix33 camera;
    VecFx32 scaled;
    VecFx32 result;
    fx32 magnitude = VEC_Mag(&gOv042CameraState->colliderOffset);
    fx64 radians;
    int index;
    fx32 cosine;
    fx32 sine;

    MTX_Copy43To33(&NNS_G3dGlb_cameraMtx, &camera);
    basis = camera;
    radians = ((fx64)degrees * FX32_PI) / (180 * 4096);
    index = (s32)(((radians * 0x10000) / (2 * FX32_PI)) & 0xffff) >> 4;
    cosine = FX_Mul(gSinFx12Table[(1024 - index) & 4095], magnitude);
    scaled = basis.rows[0];
    ScaleVecFx32InPlace(&scaled, cosine);
    gOv042CameraState->colliderOffset = scaled;
    VecFx32 *offset = &gOv042CameraState->colliderOffset;
    sine = FX_Mul(gSinFx12Table[index], magnitude);
    VEC_MultAdd(sine, &basis.rows[1], offset, &result);
    gOv042CameraState->colliderOffset = result;
}
