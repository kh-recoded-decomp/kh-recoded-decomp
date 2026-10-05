#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraState {
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
    fx32 fov;
    VecFx32 offset;
    s32 hasOffset;
    s32 unk38;
    s32 unk3c;
    s32 isRaw : 1;
    s32 isLocal : 1;
} CameraState;

typedef struct Basis3x3 {
    VecFx32 row[3];
} Basis3x3;

typedef struct BasisFrame {
    Basis3x3 basis;
    VecFx32 origin;
} BasisFrame;

typedef void (*CameraViewBuilder)(CameraState *view);

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
    u8 pad_84[0x138 - 0x84];
    void *controller;
    u8 controllerData[4];
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern int data_ov046_020c33a0[];
extern int CameraLayerIds_020c33a0[];
extern void func_ov021_020af9dc(CameraManager *camera, CameraState *state);
extern void func_ov046_020c2d8c(BasisFrame *frame);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void TransformVectorByBasis_0204bee8(const VecFx32 *vec, const Basis3x3 *basis, VecFx32 *out);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void func_02029f98(int layer, int id);
extern void func_02029f78(int layer, int id);
extern void *func_ov049_020c363c(void *data, CameraState *state, CameraState *source, int curveType, int duration, int pathMode);
extern void Camera_SetViewBuilder_020c2d4c(CameraViewBuilder builder);
extern void Camera_FollowAlongViewDirection_020c2bec(CameraState *view);
extern void Camera_AimViewAtPlayer_020c32f0(CameraState *view);
extern void func_ov046_020c0a70(void);

void Camera_StartPathViewFromState_020c1190(int pathMode, CameraState *source, int curveType, int duration, CameraViewBuilder builder)
{
    CameraState state;
    BasisFrame frame;
    VecFx32 direction;
    VecFx32 scaled;
    fx32 dot;

    func_ov021_020af9dc(g_cameraManager_020c34e0, &state);
    state.isRaw = source->isRaw;
    state.isLocal = source->isLocal;
    state.hasOffset = source->hasOffset;
    if (state.hasOffset == 1) {
        func_ov046_020c2d8c(&frame);
        VEC_Subtract_01ff9e3c(&state.position, &frame.origin, &state.position);
        TransformVectorByBasis_0204bee8(&state.position, &frame.basis, &state.position);
        TransformVectorByBasis_0204bee8(&state.target, &frame.basis, &state.target);
        TransformVectorByBasis_0204bee8(&state.up, &frame.basis, &state.up);
    }
    if (!source->isRaw) {
        direction = state.target;
        VEC_Subtract_01ff9e3c(&source->target, &state.position, &state.target);
        dot = VEC_DotProduct_01ff9e6c(&state.target, &direction);
        scaled = direction;
        ScaleVecFx32InPlace_0204a5e4(&scaled, dot);
        state.target = scaled;
        VEC_Add_01ff9e0c(&state.target, &state.position, &state.target);
    }
    if (source->isLocal) {
        state.offset = source->offset;
    }
    if (g_cameraManager_020c34e0->type != 2) {
        func_02029f98(0, data_ov046_020c33a0[g_cameraManager_020c34e0->type]);
        func_02029f78(0, CameraLayerIds_020c33a0[2]);
    }
    g_cameraManager_020c34e0->controller = func_ov049_020c363c(g_cameraManager_020c34e0->controllerData, &state, source, curveType, duration, pathMode);
    g_cameraManager_020c34e0->type = 2;
    if (builder != NULL) {
        Camera_SetViewBuilder_020c2d4c(builder);
    } else {
        switch (pathMode) {
        case 0:
            break;
        case 1:
            Camera_SetViewBuilder_020c2d4c(Camera_FollowAlongViewDirection_020c2bec);
            break;
        case 2:
            break;
        case 3:
            Camera_SetViewBuilder_020c2d4c(Camera_AimViewAtPlayer_020c32f0);
            break;
        }
    }
    if (duration == 0) {
        func_ov046_020c0a70();
    }
}

