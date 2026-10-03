#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
    int armed;
} CameraView;

typedef struct SinCos {
    fx32 cos;
    fx32 sin;
} SinCos;

extern const s16 data_0205356c[];
extern u16 GetBiasAdjustedField_0206dc80(int playerIndex);
extern void func_ov046_020c2bf8(const VecFx32 *direction, VecFx32 *out);
extern int ArmObject_020c0db4(void);
extern int Panel_DrawCounter_020c10c4(int returnMode, CameraView *view, s32 curveType, fx32 duration);

static inline SinCos GetSinCos(int index)
{
    SinCos result;
    result.cos = data_0205356c[(0x400 - index) & 0xfff];
    result.sin = data_0205356c[index];
    return result;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

void Camera_BlendToPlayerBackView_020c1360(s32 curveType, fx32 duration)
{
    CameraView view;
    SinCos angle = GetSinCos(GetBiasAdjustedField_0206dc80(0) >> 4);

    view.direction = MakeVec(-angle.sin, 0, -angle.cos);
    func_ov046_020c2bf8(&view.direction, &view.position);
    view.up = MakeVec(0, 0x1000, 0);
    view.armed = ArmObject_020c0db4();
    Panel_DrawCounter_020c10c4(1, &view, curveType, duration);
}
