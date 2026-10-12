#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraState {
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
    fx32 fov;
    VecFx32 offset;
    int hasOffset;
    int unk38;
    int unk3c;
    s32 isRaw : 1;
    s32 isLocal : 1;
    s32 unknownFlag2 : 1;
} CameraState;

typedef struct BasisFrame {
    VecFx32 axes[3];
    VecFx32 origin;
} BasisFrame;

typedef struct CameraManager {
    u8 pad_00[0x134];
    fx32 viewDistance;
} CameraManager;

extern CameraManager *gCameraManager;
extern fx32 func_ov046_020c0dd4(void);
extern void Camera_AimViewAtPlayer(CameraState *state);
extern void Camera_GetRaisedPlayerPosition(VecFx32 *out);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void Camera_BuildSideView(BasisFrame *frame);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void TransformVectorByBasis(const VecFx32 *vec, const VecFx32 *axes, VecFx32 *out);
extern void func_ov046_020c11a0(int mode, CameraState *state, int curve, int duration);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

void Camera_StartLocalTargetView(const VecFx32 *position, int curve, int duration)
{
    CameraState state;
    VecFx32 focus;
    BasisFrame frame;

    state.position = *position;
    state.fov = func_ov046_020c0dd4();
    Camera_AimViewAtPlayer(&state);
    state.isRaw = 0;
    state.isLocal = 1;
    state.hasOffset = 1;
    state.unknownFlag2 = 0;
    state.unk38 = 0;
    state.unk3c = 0;
    state.offset = MakeVec(0, 0x1000, 0);
    Camera_GetRaisedPlayerPosition(&focus);
    gCameraManager->viewDistance = VEC_Distance(&focus, position);
    state.target = focus;
    Camera_BuildSideView(&frame);
    VEC_Subtract(&state.position, &frame.origin, &state.position);
    VEC_Subtract(&state.target, &frame.origin, &state.target);
    TransformVectorByBasis(&state.position, frame.axes, &state.position);
    TransformVectorByBasis(&state.target, frame.axes, &state.target);
    TransformVectorByBasis(&state.up, frame.axes, &state.up);
    func_ov046_020c11a0(3, &state, curve, duration);
}
