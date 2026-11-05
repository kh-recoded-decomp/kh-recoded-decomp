#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraModeEntry {
    u8 pad_00[0x50];
    s32 state;
} CameraModeEntry;

typedef struct CameraManager {
    u8 pad_00[0x134];
    fx32 mode3Value;
} CameraManager;

extern CameraManager *gCameraManager;
extern void UpdateOrbitCameraInputFollowAndDrift(CameraModeEntry *entry, CameraManager *manager);
extern CameraModeEntry *Camera_GetTopDownView(void);
extern int Camera_GetModeValue(void);

void SetCameraMode3EntryState(int state)
{
    CameraManager *manager;
    CameraModeEntry *entry;

    if (Camera_GetModeValue() == 3) {
        entry = Camera_GetTopDownView();
        manager = gCameraManager;
        UpdateOrbitCameraInputFollowAndDrift(entry, gCameraManager);
        entry->state = state;
        if (state == 1) {
            manager->mode3Value = 0x6000;
        }
    }
}
