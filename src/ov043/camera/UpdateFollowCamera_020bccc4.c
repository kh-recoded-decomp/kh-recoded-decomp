#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} VecFx2;

typedef struct {
    u8 _0[0x8];
    fx32 depth;
    fx32 nearClip;
    fx32 farClip;
    VecFx32 eye;
    VecFx32 target;
    u8 _2c[0x18];
    u32 followLocked;
    u32 lockTimer;
    fx32 orbitWidth;
    fx32 orbitHeight;
    fx32 heightScale;
    VecFx32 goalTarget;
    VecFx32 goalEye;
    VecFx32 shake;
    VecFx32 eyeOffset;
    VecFx32 liveTarget;
    VecFx32 liveEye;
    u8 _a0[8];
    u32 particle;
    u8 _ac[0xc];
    VecFx32 particlePos;
} CameraState;

extern CameraState *data_ov043_020bd2c0;
extern s16 data_0205356c[];
extern int func_ov001_02063a4c(void);
extern int func_ov001_02067ed4(void);
extern fx32 *func_ov001_0206dc4c(int index);
extern int func_ov021_020af84c(void);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void MoveCameraTargetTo_020bc974(const VecFx32 *pos);
extern BOOL EaseCameraVectors_020bcf44(void);
extern void func_ov021_020afb94(void *particle);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline fx32 FxMul(fx32 a, fx32 b) {
    return (fx32)(((fx64)a * b + 0x800LL) >> 12);
}

static inline fx32 Vec2LengthP(const VecFx2 *v) {
    return FX_Sqrt_01ff9cfc((fx32)(((fx64)v->x * v->x + (fx64)v->y * v->y) >> 12));
}

static inline void ApplyCameraShake(void) {
    CameraState **ref = &data_ov043_020bd2c0;
    CameraState *camera;
    VecFx32 targetSum;
    VecFx32 eyeSum;
    if ((*ref)->particle != 0) {
        func_ov021_020afb94(&(*ref)->particle);
        (*ref)->shake = (*ref)->particlePos;
    }
    camera = *ref;
    VEC_Add_01ff9e0c(&camera->goalTarget, &camera->shake, &targetSum);
    camera->target = targetSum;
    VEC_Add_01ff9e0c(&(*ref)->goalEye, &(*ref)->shake, &eyeSum);
    camera->eye = eyeSum;
}

// Camera and follow as parameters fix register order
BOOL UpdateFollowCamera_020bccc4(CameraState *camera, fx32 *follow) {
    VecFx32 pos;
    int index;
    fx32 sine;
    fx32 cosine;
    fx32 lift;
    fx32 vertical;
    VecFx2 scratch;
    VecFx2 extent;
    camera = data_ov043_020bd2c0;
    if (func_ov001_02063a4c() != 4 && func_ov001_02063a4c() != 7 && func_ov001_02063a4c() != 8) {
        return FALSE;
    }
    camera->farClip = func_ov001_02067ed4() == 0xe ? 0x578000 : 0x7d000;
    switch (camera->followLocked) {
    case 0:
        follow = func_ov001_0206dc4c(0);
        index = func_ov021_020af84c() >> 4;
        pos = camera->eyeOffset;
        sine = data_0205356c[index];
        if (sine < 0) {
            sine = -sine;
        }
        vertical = FxMul(FxMul(camera->orbitHeight, camera->depth), sine);
        cosine = data_0205356c[(0x400 - index) & 0xfff];
        if (cosine < 0) {
            cosine = -cosine;
        }
        extent.x = FxMul(camera->orbitWidth, cosine);
        extent.y = vertical;
        scratch = extent;
        pos.x += FxMul(follow[0], Vec2LengthP(&scratch));
        pos.z = data_ov043_020bd2c0->goalEye.z;
        MoveCameraTargetTo_020bc974(&pos);
        lift = FxMul(follow[1] < 0 ? 0 : follow[1], camera->heightScale);
        data_ov043_020bd2c0->liveEye.y = camera->eyeOffset.y + FxMul(lift, 0xe66);
        data_ov043_020bd2c0->liveTarget.y = camera->eyeOffset.y + FxMul(follow[1] < 0 ? 0 : follow[1], camera->heightScale);
        EaseCameraVectors_020bcf44();
        break;
    }
    ApplyCameraShake();
    return FALSE;
}
