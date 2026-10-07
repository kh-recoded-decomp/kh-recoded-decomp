#include "nitro/types.h"

typedef struct CameraOverrideView {
    u32 data[12];
} CameraOverrideView;

typedef struct EventCameraWork {
    u8 pad_00[0x34];
    int pathKind;
    u8 pad_38[0xf0];
    CameraOverrideView directView;
    CameraOverrideView pathView;
    BOOL pathViewSet;
    void *activePath;
} EventCameraWork;

extern s32 Camera_GetModeValue(void);
extern EventCameraWork *Camera_GetEventWork(void);

BOOL CameraPath_SetOverrideView(const CameraOverrideView *view)
{
    EventCameraWork *work;

    if (Camera_GetModeValue() == 2) {
        work = Camera_GetEventWork();
        if (work->activePath != NULL) {
            if (work->pathKind == 2) {
                work->directView = *view;
            } else {
                work->pathView = *view;
                work->pathViewSet = TRUE;
            }
            return TRUE;
        }
    }
    return FALSE;
}
