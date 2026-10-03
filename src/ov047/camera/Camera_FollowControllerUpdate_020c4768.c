#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTracking {
    u8 pad_00[0x9c];
    fx32 savedHeight;
} CameraTracking;

typedef struct CameraManager {
    u8 pad_00[0xe4];
    s32 followPreset;
    u8 pad_e8[0xf0 - 0xe8];
    u32 stateFlags;
} CameraManager;

extern BOOL Camera_IsFrozen_020c0c1c(void);
extern BOOL IsLeaderFlag3Active_0206e198(void);
extern int func_ov001_02063a4c(void);
extern fx32 func_ov046_020c1a48(int preset);
extern void *func_ov047_020c3b5c(void **next);
extern void Camera_UpdateManualTurn_020c4668(void);
extern void Camera_ResetFollowHeading_020c464c(void);
extern int func_02029f48(void);
extern BOOL Camera_UpdateTracking_020c631c(BOOL snap);

void *Camera_FollowControllerUpdate_020c4768(CameraTracking *tracking, CameraManager *camera)
{
    void *next = NULL;
    void *result;

    if (Camera_IsFrozen_020c0c1c()) {
        return NULL;
    }
    if (!IsLeaderFlag3Active_0206e198()) {
        return NULL;
    }
    if (func_ov001_02063a4c() != 4) {
        tracking->savedHeight = func_ov046_020c1a48(camera->followPreset);
        camera->stateFlags &= 0x100c0003;
    } else if (!(camera->stateFlags & 0x40000)) {
        result = func_ov047_020c3b5c(&next);
        if (result != NULL) {
            return result;
        }
    } else if (camera->stateFlags & 0x800000) {
        Camera_ResetFollowHeading_020c464c();
    } else {
        Camera_UpdateManualTurn_020c4668();
    }
    Camera_UpdateTracking_020c631c(func_02029f48() == -16);
    return next;
}

