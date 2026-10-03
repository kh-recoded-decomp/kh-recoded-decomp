#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
    u8 pad_84[0x138 - 0x84];
    void *controller;
    u8 controllerData[4];
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern int data_ov046_020c33a0[];
extern void func_02029f98(int layer, int id);
extern void func_02029f78(int layer, int id);
extern void *func_ov047_020c70d8(void *data, CameraManager *camera, void *view);
extern void *func_ov048_020c3858(void *data, CameraManager *camera, void *view);
extern void *func_ov050_020c3ba4(void *data, CameraManager *camera, void *view);

void Camera_SetViewMode_020c1038(int mode, void *view)
{
    func_02029f98(0, data_ov046_020c33a0[g_cameraManager_020c34e0->type]);
    func_02029f78(0, data_ov046_020c33a0[mode]);
    g_cameraManager_020c34e0->type = mode;
    switch (mode) {
    case 0:
        g_cameraManager_020c34e0->controller = func_ov047_020c70d8(g_cameraManager_020c34e0->controllerData, g_cameraManager_020c34e0, view);
        break;
    case 1:
        g_cameraManager_020c34e0->controller = func_ov048_020c3858(g_cameraManager_020c34e0->controllerData, g_cameraManager_020c34e0, view);
        break;
    case 2:
        break;
    case 3:
        g_cameraManager_020c34e0->controller = func_ov050_020c3ba4(g_cameraManager_020c34e0->controllerData, g_cameraManager_020c34e0, view);
        break;
    }
}

