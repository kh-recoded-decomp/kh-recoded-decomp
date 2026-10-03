#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SinCos {
    fx32 cos;
    fx32 sin;
} SinCos;

typedef struct CameraTracking {
    u8 pad_00[0x10];
    u32 angle;
    u8 pad_14[0x40];
    VecFx32 direction;
} CameraTracking;

typedef struct CameraManager {
    u8 pad_00[0x2c];
    VecFx32 up;
} CameraManager;

extern const s16 data_0205356c[];
extern u16 Math_AsinIdx_0202aaa8(int sine);
extern void func_0204b0ac(VecFx32 *vec, const VecFx32 *axis, fx32 radians);

static inline SinCos GetSinCos(int index)
{
    SinCos result;
    result.cos = data_0205356c[(0x400 - index) & 0xfff];
    result.sin = data_0205356c[index];
    return result;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

void Camera_UpdateUpVector_020c603c(CameraTracking *tracking, CameraManager *camera)
{
    int pitch = tracking->direction.y;

    if (pitch < 0) {
        pitch = -pitch;
    }
    if (pitch > 16) {
        VecFx32 axis;
        SinCos sc;

        sc = GetSinCos((u16)tracking->angle >> 4);
        camera->up = MakeVec(sc.sin, 0, sc.cos);
        axis = MakeVec(0, 0x1000, 0);
        func_0204b0ac(&camera->up, &axis, (fx32)((s64)Math_AsinIdx_0202aaa8(-tracking->direction.y) * 0x6488 / 0x10000) + 0x1922);
    } else {
        camera->up.x = 0;
        camera->up.y = 0x1000;
        camera->up.z = 0;
    }
}
