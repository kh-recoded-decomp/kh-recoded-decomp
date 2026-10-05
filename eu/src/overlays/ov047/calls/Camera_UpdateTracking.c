#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTracking {
    u8 pad_00[0xc];
    fx32 distance;
    u32 angle;
    u32 unk_14;
    u8 pad_18[0x4];
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
    VecFx32 unk_7C;
    u8 pad_88[0x2c];
    u32 unk_B4;
} CameraTracking;

typedef struct CameraManager {
    u8 pad_00[0x38];
    VecFx32 eye;
    u8 pad_44[0xf8];
    CameraTracking tracking;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void func_ov047_020c5db0(CameraTracking *tracking, CameraManager *camera);
extern void func_ov047_020c53d4(CameraTracking *tracking, CameraManager *camera, void *context);
extern void func_ov047_020c50e0(CameraTracking *tracking, CameraManager *camera, void *context);
extern void func_ov047_020c5568(CameraTracking *tracking, CameraManager *camera, void *context);
extern void Camera_ConstrainEye(CameraTracking *tracking, CameraManager *camera);
extern void Camera_UpdateUpVector(CameraTracking *tracking, CameraManager *camera);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL Camera_UpdateTracking(void *context)
{
    CameraManager *camera = data_ov046_020c3500;
    CameraTracking *tracking = &camera->tracking;

    tracking->prevLookAt = tracking->lookAt;
    tracking->unk_60 = tracking->unk_54;
    tracking->unk_6C = tracking->unk_7C;
    tracking->unk_20 = tracking->unk_1C;
    tracking->unk_78 = tracking->unk_14;
    func_ov047_020c5db0(tracking, camera);
    func_ov047_020c53d4(tracking, camera, context);
    func_ov047_020c50e0(tracking, camera, context);
    func_ov047_020c5568(tracking, camera, context);
    Camera_ConstrainEye(tracking, camera);
    Camera_UpdateUpVector(tracking, camera);
    tracking->distance = VEC_Distance(&camera->eye, &tracking->target);
    tracking->unk_B4 = 0;
    return TRUE;
}
