#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    u8 pad_0C[0x1c];
} CameraView;

typedef struct CameraManager CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void func_ov021_020af9dc(CameraManager *camera, CameraView *view);
extern void func_ov046_020c1038(s32 mode, CameraView *view);

void Camera_ChangeModeFromCurrentView_020c1014(s32 mode)
{
    CameraView view;

    func_ov021_020af9dc(g_cameraManager_020c34e0, &view);
    func_ov046_020c1038(mode, &view);
}
