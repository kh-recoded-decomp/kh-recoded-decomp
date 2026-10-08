#include "nitro/types.h"

typedef unsigned int CameraTargetCallback(unsigned int target);

typedef struct CameraTarget {
    u8 pad_000[0x21c];
    CameraTargetCallback *callback;
} CameraTarget;

typedef struct CameraTracking {
    u8 pad_00[0x0c];
    u32 activeDistance;
    u8 pad_10[0x94 - 0x10];
    u32 modeDistance;
    u8 pad_98[4];
    u32 computedDistance;
} CameraTracking;

typedef struct CameraManager {
    u8 pad_000[0xe4];
    u32 modeIndex;
    u8 pad_0e8[0xf0 - 0xe8];
    u32 flags;
} CameraManager;

extern u16 data_02060500;
extern CameraTarget *GetBoundedEntryField(int index);
extern u32 Camera_ComputeFollowDistance(u32 index);
extern u32 func_ov046_020c1a68(u32 index);
extern int func_ov046_020c2ad8(CameraManager *camera);

void Camera_HandleDistanceToggle(CameraTracking *tracking, CameraManager *camera)
{
    CameraTarget *target;
    int blocked;
    u32 value;
    u32 flags;

    if (((camera->flags & 0x40000) == 0) && ((camera->flags & 0x200) == 0) &&
        ((data_02060500 & 4) != 0)) {
        flags = 0;
        target = GetBoundedEntryField(0);
        if (target->callback != NULL) {
            flags = target->callback((u32)target);
        }
        if (((flags & 8) == 0) && (blocked = func_ov046_020c2ad8(camera), blocked == 0)) {
            camera->flags ^= 0x80000;
            value = Camera_ComputeFollowDistance(camera->modeIndex);
            tracking->modeDistance = value;
            value = func_ov046_020c1a68(camera->modeIndex);
            tracking->computedDistance = value;
        }
    }
    tracking->activeDistance = tracking->modeDistance;
}
