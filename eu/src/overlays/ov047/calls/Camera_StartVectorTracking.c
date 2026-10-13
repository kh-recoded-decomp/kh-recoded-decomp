#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTracking {
    u8 reserved00[0x0c];
    fx32 distance;
    u32 angle;
    fx32 height;
    fx32 verticalOffset;
    u8 reserved1c[8];
    VecFx32 lookAt;
    VecFx32 target;
    u8 reserved3c[0x18];
    VecFx32 direction;
    u8 reserved60[0x1c];
    VecFx32 savedLookAt;
    VecFx32 savedTarget;
    fx32 savedDistance;
    u32 savedAngle;
    u8 reserved9c[0x1c];
    u16 pitch;
    u16 savedPitch;
} CameraTracking;
typedef struct CameraManager {
    u8 reserved00[0x44];
    VecFx32 target;
    u8 reserved50[0x94];
    s32 mode;
} CameraManager;
/* Position and direction supplied by the camera view-mode transition. */
typedef struct CameraVectorTarget {
    VecFx32 position;
    VecFx32 direction;
    u8 reserved18[0x0c];
    fx32 pitchRadians;
} CameraVectorTarget;
typedef void *(*CameraUpdateFn)(CameraTracking *, CameraManager *);

enum { CAMERA_TURN_RADIANS = 0x6488 };

extern CameraUpdateFn Camera_ResetTracking(CameraTracking *, CameraManager *);
extern BOOL func_ov046_020c2ad8(CameraManager *);
extern fx32 func_ov046_020c1a68(s32);
extern void *Camera_FollowControllerUpdate(CameraTracking *, CameraManager *);
extern const VecFx32 *Camera_GetFocusPosition(void);
extern u16 FX_Atan2Idx(fx32, fx32);
extern fx32 VEC_Distance(const VecFx32 *, const VecFx32 *);
extern void VEC_Subtract(const VecFx32 *, const VecFx32 *, VecFx32 *);
extern fx32 VEC_DotProduct(const VecFx32 *, const VecFx32 *);
extern void ScaleVecFx32InPlace(VecFx32 *, fx32);
extern void VEC_Add(const VecFx32 *, const VecFx32 *, VecFx32 *);

static inline VecFx32 MakeVector(fx32 x, fx32 y, fx32 z)
{
    VecFx32 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
static inline VecFx32 SubtractVector(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 v;
    VEC_Subtract(a, b, &v);
    return v;
}
static inline VecFx32 ScaleVector(const VecFx32 *a, fx32 scale)
{
    VecFx32 v = *a;
    ScaleVecFx32InPlace(&v, scale);
    return v;
}
static inline VecFx32 AddVector(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 v;
    VEC_Add(a, b, &v);
    return v;
}

CameraUpdateFn Camera_StartVectorTracking(CameraTracking *tracking,
                                       CameraManager *camera,
                                       const CameraVectorTarget *params)
{
    VecFx32 focus;
    VecFx32 projection;
    VecFx32 displacement;

    Camera_ResetTracking(tracking, camera);
    if (!func_ov046_020c2ad8(camera)) {
        tracking->savedAngle = FX_Atan2Idx(-params->direction.x, -params->direction.z);
        tracking->angle = tracking->savedAngle;
    } else {
        tracking->savedAngle = 0;
        tracking->angle = 0;
    }
    tracking->height = func_ov046_020c1a68(camera->mode);
    focus = MakeVector(Camera_GetFocusPosition()->x,
                       Camera_GetFocusPosition()->y + tracking->verticalOffset,
                       Camera_GetFocusPosition()->z);
    tracking->distance = VEC_Distance(&params->position, &focus);
    /* One turn is 2*pi in the fixed-point radians used by this preset. */
    tracking->savedPitch = ((s64)params->pitchRadians * 0x10000) / CAMERA_TURN_RADIANS & 0xffff;
    tracking->pitch = tracking->savedPitch;
    tracking->lookAt = params->position;
    tracking->savedLookAt = tracking->lookAt;
    tracking->savedTarget = *Camera_GetFocusPosition();
    tracking->savedTarget.y += tracking->verticalOffset;
    displacement = SubtractVector(&tracking->savedTarget, &params->position);
    projection = ScaleVector(&params->direction, VEC_DotProduct(&displacement, &params->direction));
    camera->target = AddVector(&params->position, &projection);
    tracking->target = camera->target;
    tracking->verticalOffset = camera->target.y - Camera_GetFocusPosition()->y;
    tracking->direction = params->direction;
    return Camera_FollowControllerUpdate;
}
