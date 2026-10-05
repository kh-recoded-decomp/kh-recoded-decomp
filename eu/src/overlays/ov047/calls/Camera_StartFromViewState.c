#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    u8 pad_00[0x14];
    VecFx32 position;
    VecFx32 lookAt;
    u8 pad_2C[0xc];
} CameraView;

typedef struct CameraTracking {
    u8 pad_00[0xc];
    fx32 distance;
    u32 angle;
    fx32 height;
    fx32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    VecFx32 lookAt;
    VecFx32 target;
    VecFx32 prevLookAt;
    u8 pad_48[0xc];
    VecFx32 unk_54;
    VecFx32 unk_60;
    VecFx32 unk_6C;
    u32 unk_78;
    VecFx32 savedLookAt;
    VecFx32 savedTarget;
    fx32 savedDistance;
    u32 savedAngle;
    fx32 savedHeight;
    fx32 savedUnk18;
} CameraTracking;

typedef struct CameraManager {
    CameraView view;
    VecFx32 eye;
    u8 pad_44[0xa0];
    int mode;
    int prevMode;
    u8 pad_EC[0x4];
    u32 flags;
    u8 pad_F4[0x48];
    CameraTracking tracking;
} CameraManager;

typedef struct CameraViewState {
    CameraView view;
    u32 angle;
    fx32 distance;
    fx32 unk_40;
    fx32 unk_44;
} CameraViewState;

extern CameraManager *data_ov046_020c3500;

extern fx32 Camera_ComputeFollowDistance(int mode);
extern fx32 func_ov046_020c1a68(int mode);
extern void Camera_RestoreSavedTracking(void);

void Camera_StartFromViewState(CameraViewState *src, u32 angle, CameraViewState *out)
{
    CameraManager *camera = data_ov046_020c3500;
    CameraTracking *tracking = &camera->tracking;

    camera->flags &= 0xfff7ffff;
    tracking->savedDistance = Camera_ComputeFollowDistance(camera->mode);
    tracking->savedHeight = func_ov046_020c1a68(camera->mode);
    tracking->lookAt = src->view.lookAt;
    tracking->savedLookAt = tracking->lookAt;
    tracking->angle = (u16)angle;
    tracking->savedAngle = (u16)angle;
    tracking->height = tracking->savedHeight;
    tracking->savedUnk18 = tracking->unk_18;
    Camera_RestoreSavedTracking();
    camera->view.lookAt = camera->eye;
    camera->view.position = tracking->target;
    out->unk_40 = tracking->distance;
    out->unk_44 = tracking->unk_18;
    out->view = camera->view;
    out->distance = tracking->distance;
}
