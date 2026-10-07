#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPath {
    void *nodes;
    u16 nodeCount;
    u8 pad_06[0x46];
    s32 curveType;
    fx32 duration;
} CameraPath;

typedef struct EventCameraWork {
    u8 pad_00[0x18c];
    CameraPath *activePath;
} EventCameraWork;

extern s32 Camera_GetModeValue(void);
extern EventCameraWork *Camera_GetEventWork(void);
extern void Camera_BlendToFollowView(s32 curveType, fx32 duration);

BOOL Camera_ReturnFromPathView(void)
{
    CameraPath *path;

    if (Camera_GetModeValue() == 2) {
        path = Camera_GetEventWork()->activePath;
        if (path != NULL) {
            Camera_BlendToFollowView(path->curveType, path->duration);
            return TRUE;
        }
    }
    return FALSE;
}
