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

extern BOOL Camera_IsFrozen(void);
extern BOOL IsLeaderFlag3Active(void);
extern int func_ov001_02063a4c(void);
extern fx32 func_ov046_020c1a68(int preset);
extern void *func_ov047_020c3b7c(void **next);
extern void Camera_UpdateManualTurn(void);
extern void Camera_ResetFollowHeading(void);
extern int func_02029f5c(void);
extern BOOL Camera_UpdateTracking(BOOL snap);

void *Camera_FollowControllerUpdate(CameraTracking *tracking, CameraManager *camera)
{
    void *next = NULL;
    void *result;

    if (Camera_IsFrozen()) {
        return NULL;
    }
    if (!IsLeaderFlag3Active()) {
        return NULL;
    }
    if (func_ov001_02063a4c() != 4) {
        tracking->savedHeight = func_ov046_020c1a68(camera->followPreset);
        camera->stateFlags &= 0x100c0003;
    } else if (!(camera->stateFlags & 0x40000)) {
        result = func_ov047_020c3b7c(&next);
        if (result != NULL) {
            return result;
        }
    } else if (camera->stateFlags & 0x800000) {
        Camera_ResetFollowHeading();
    } else {
        Camera_UpdateManualTurn();
    }
    Camera_UpdateTracking(func_02029f5c() == -16);
    return next;
}
