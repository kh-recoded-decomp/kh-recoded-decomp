#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CameraManager {
    fx32 sideOffset;
    fx32 aspect;
    fx32 tanHalf;
    u8 pad_0c[0x50 - 0x0c];
    VecFx32 upAxis;
    VecFx32 sideAxis;
    VecFx32 rotatedUp;
    VecFx32 reflectedUp;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern MtxFx43 data_0205a970;

extern void MTX_Copy43To33_01ff913c(const MtxFx43 *src, MtxFx33 *dst);
extern u16 Math_AsinIdx_0202aaa8(int sine);
extern void func_0204b0ac(VecFx32 *vec, const VecFx32 *axis, fx32 angle);
extern VecFx32 ReflectVectorAcrossNormal_0204adf8(const VecFx32 *vec, const VecFx32 *normal);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern int FixedPointMultiply12(int left, int right);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);

void Camera_UpdateViewAxes_020c0c34(void)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    MtxFx33 view;
    VecFx32 reflectedUp;
    VecFx32 upAxis;
    MtxFx33 fetched;
    VecFx32 up;
    VecFx32 side;
    VecFx32 sum;
    fx32 scale;
    fx32 angle;

    MTX_Copy43To33_01ff913c(&data_0205a970, &fetched);
    view = fetched;
    angle = (fx32)((s64)Math_AsinIdx_0202aaa8(camera->sideOffset) * 0x6488 / 0x10000);
    up = *(VecFx32 *)view.m[1];
    func_0204b0ac(&up, (VecFx32 *)view.m[2], angle);
    g_cameraManager_020c34e0->rotatedUp = up;
    reflectedUp = ReflectVectorAcrossNormal_0204adf8(&g_cameraManager_020c34e0->rotatedUp, (VecFx32 *)view.m[2]);
    g_cameraManager_020c34e0->reflectedUp = reflectedUp;
    scale = FX_Div_01ff9c84(0x1000, camera->tanHalf);
    scale = FixedPointMultiply12(camera->aspect, scale);
    side = *(VecFx32 *)view.m[0];
    ScaleVecFx32InPlace_0204a5e4(&side, scale);
    g_cameraManager_020c34e0->sideAxis = side;
    VEC_MultAdd_01ffa09c(camera->sideOffset, (VecFx32 *)view.m[2], &g_cameraManager_020c34e0->sideAxis, &sum);
    g_cameraManager_020c34e0->sideAxis = sum;
    VEC_Normalize_01ff9f88(&g_cameraManager_020c34e0->sideAxis, &g_cameraManager_020c34e0->sideAxis);
    upAxis = ReflectVectorAcrossNormal_0204adf8(&g_cameraManager_020c34e0->sideAxis, (VecFx32 *)view.m[2]);
    g_cameraManager_020c34e0->upAxis = upAxis;
}

