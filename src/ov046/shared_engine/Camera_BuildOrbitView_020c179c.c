#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrbitCameraView {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
    fx32 fieldOfView;
} OrbitCameraView;

typedef struct OrbitFollowControl {
    u8 reserved00[0x10];
    u32 goalHeading;
    u8 reserved14[0x98 - 0x14];
    u32 currentHeading;
} OrbitFollowControl;

typedef struct OrbitCameraManager {
    u8 reserved00[0x80];
    int mode;
    u8 reserved84[0xe4 - 0x84];
    int followPreset;
    u8 reservedE8[0x13c - 0xe8];
    OrbitFollowControl follow;
} OrbitCameraManager;

extern OrbitCameraManager *gCameraManager;
extern const s16 gSinFx12Table[];
extern fx32 Camera_ComputeFollowDistance(int preset);
extern fx32 GetCameraOrbitHeight(int preset);
extern fx32 Camera_GetModeDistance(int preset);
extern fx32 FX_Sqrt(fx32 value);
extern const VecFx32 *Camera_GetFocusPosition(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern void Camera_ResolveCollision(VecFx32 *point);
extern void func_ov046_020c1fa0(VecFx32 *focus, OrbitCameraView *view);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_NormalizeLength(const VecFx32 *vector, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vector, fx32 scale);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void DivideVecByLength(VecFx32 *vector, fx32 divisor);
extern void VEC_Normalize(const VecFx32 *vector, VecFx32 *out);

static inline fx32 RoundedProduct(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

static inline VecFx32 MakeVector(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

void Camera_BuildOrbitView_020c179c(OrbitCameraView *view, u16 heading)
{
    OrbitCameraManager *camera = gCameraManager;
    fx32 distance = Camera_ComputeFollowDistance(camera->followPreset);
    fx32 height = GetCameraOrbitHeight(camera->followPreset);
    fx32 focusHeight = Camera_GetModeDistance(camera->followPreset);
    fx32 radius = FX_Sqrt(RoundedProduct(distance, distance) - RoundedProduct(height, height));
    const VecFx32 *source = Camera_GetFocusPosition();
    VecFx32 focus;
    fx32 focusX = source->x;
    fx32 focusZ = source->z;
    fx32 focusY = source->y + focusHeight;
    focus.x = focusX;
    focus.y = focusY;
    focus.z = focusZ;
    int index = heading >> 4;
    fx32 sine = FX_Mul(-gSinFx12Table[index], radius);
    VecFx32 offset;
    offset.x = FX_Mul(-gSinFx12Table[(0x400 - index) & 0xfff], radius);
    offset.z = sine;
    offset.y = height;
    VEC_Add(&focus, &offset, &view->position);

    if (camera->mode == 0) {
        OrbitFollowControl *follow = &gCameraManager->follow;
        follow->currentHeading = FX_Atan2Idx(offset.x, offset.z);
        follow->goalHeading = follow->currentHeading;
    }
    Camera_ResolveCollision(&focus);
    func_ov046_020c1fa0(&focus, view);
    if (VEC_Distance(&view->position, &focus) < 0x80) {
        view->direction = offset;
        VEC_NormalizeLength(&view->direction, &view->direction);
        ScaleVecFx32InPlace(&view->direction, -0x80);
        VEC_Subtract(&focus, &view->direction, &view->position);
        DivideVecByLength(&view->direction, 0x80);
    } else {
        VecFx32 direction;
        VecFx32 delta;
        VecFx32 input;
        VEC_Subtract(&focus, &view->position, &delta);
        input = delta;
        VEC_Normalize(&input, &direction);
        view->direction = direction;
    }
    view->up = MakeVector(0, 0x1000, 0);
    view->fieldOfView = 0x860;
}
