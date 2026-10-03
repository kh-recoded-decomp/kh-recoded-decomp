#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RotationMtx {
    fx32 m[4][3];
} RotationMtx;

typedef struct CameraLens {
    fx32 zoom;
    fx32 tilt;
    u8 pad_08[4];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 pivot;
    VecFx32 eye;
} CameraLens;

typedef struct EventCameraManager {
    u8 pad_00[0x38];
    VecFx32 offset;
    s32 pitch;
    s32 yaw;
    u8 pad_4c[0x80 - 0x4c];
    fx32 distance;
    u8 pad_84[0x9c - 0x84];
    u32 followActorId;
    u8 pad_a0[0x140 - 0xa0];
    u8 transform[0x10];
    CameraLens lens;
} EventCameraManager;

typedef struct FollowActor {
    u8 pad_00[0xa8];
    VecFx32 position;
} FollowActor;

extern EventCameraManager *data_ov001_020a04f4;
extern FollowActor *func_02036240(u16 actorId);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void Transform_SetBasePos_0203ab9c(void *transform, const VecFx32 *pos);
extern void CamAnim_Update_0203aafc(void *transform);
extern void func_ov001_0208af4c(RotationMtx *mtx, u16 yaw, u16 pitch);
extern void MTX_MultVec43_01ff9ad8(const VecFx32 *vec, const RotationMtx *mtx, VecFx32 *dst);
extern void func_ov021_020af4ac(CameraLens *lens);

void UpdateEventCameraTransform_0208afb8(void) {
    EventCameraManager *manager = data_ov001_020a04f4;
    VecFx32 base;
    RotationMtx rotation;

    if (manager->followActorId != (u32)-1) {
        base = func_02036240(manager->followActorId)->position;
        VEC_Add_01ff9e0c(&base, &manager->offset, &base);
    } else {
        base = manager->offset;
    }
    Transform_SetBasePos_0203ab9c(manager->transform, &base);
    CamAnim_Update_0203aafc(manager->transform);
    if (manager->pitch != 0 || manager->yaw != 0 || manager->distance != 0) {
        VEC_Subtract_01ff9e3c(&manager->lens.eye, &manager->lens.pivot, &manager->lens.eye);
        manager->lens.eye.z += manager->distance;
        func_ov001_0208af4c(&rotation, manager->yaw, manager->pitch);
        MTX_MultVec43_01ff9ad8(&manager->lens.eye, &rotation, &manager->lens.eye);
        VEC_Add_01ff9e0c(&manager->lens.eye, &manager->lens.pivot, &manager->lens.eye);
    }
    if (manager->lens.zoom <= 0) {
        manager->lens.zoom = 1;
    } else if (manager->lens.zoom >= 0x1000) {
        manager->lens.zoom = 0xfff;
    }
    if (manager->lens.tilt <= -0x1000) {
        manager->lens.tilt = -0xfff;
    } else if (manager->lens.tilt >= 0x1000) {
        manager->lens.tilt = 0xfff;
    }
    manager->lens.farClip = 0x6a4000;
    manager->lens.nearClip = 0x19a;
    func_ov021_020af4ac(&manager->lens);
}
