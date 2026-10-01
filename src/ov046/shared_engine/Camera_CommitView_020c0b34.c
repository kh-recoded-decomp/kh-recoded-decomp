#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    u32 mode;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void camera_commit_projection_0202a814(void *camera);
extern void func_ov046_020c0c34(void);
extern void func_ov047_020c3500(void *camera);

void Camera_CommitView_020c0b34(void *camera)
{
    camera_commit_projection_0202a814(camera);
    func_ov046_020c0c34();
    switch (g_cameraManager_020c34e0->mode) {
    case 0:
        func_ov047_020c3500(camera);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
