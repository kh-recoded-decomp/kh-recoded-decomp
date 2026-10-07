#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraViewSnapshot {
    u32 data[17];
} CameraViewSnapshot;

typedef struct CameraPathNode {
    CameraViewSnapshot view;
    s32 curveType;
    fx32 duration;
} CameraPathNode;

typedef struct CameraPath {
    CameraPathNode *nodes;
    u16 nodeCount;
    u16 currentNode;
    CameraViewSnapshot returnView;
    u8 pad_4c[0x10];
    int elapsed;
} CameraPath;

typedef struct EventCameraWork {
    u8 pad_00[0x44];
    CameraViewSnapshot currentView;
    u8 pad_88[0x100];
    int pathElapsed;
    CameraPath *activePath;
} EventCameraWork;

extern s32 Camera_GetModeValue(void);
extern EventCameraWork *Camera_GetEventWork(void);
extern int func_ov046_020c11a0(s32 cameraType, CameraPathNode *node, s32 curveType, fx32 duration);

void CameraPath_Start(CameraPath *path)
{
    EventCameraWork *work;

    path->currentNode = 0;
    func_ov046_020c11a0(Camera_GetModeValue(), &path->nodes[path->currentNode],
                               path->nodes[path->currentNode].curveType,
                               path->nodes[path->currentNode].duration);
    work = Camera_GetEventWork();
    path->returnView = work->currentView;
    path->elapsed = 0;
    work->activePath = path;
    work->pathElapsed = 0;
}
