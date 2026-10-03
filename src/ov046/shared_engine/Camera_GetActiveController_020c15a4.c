#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void *func_ov047_020c380c(void);
extern void *func_ov048_020c3844(void);
extern void *func_ov049_020c4220(void);
extern void *func_ov050_020c3b9c(void);

void *Camera_GetActiveController_020c15a4(void)
{
    switch (g_cameraManager_020c34e0->type) {
    case 0:
        return func_ov047_020c380c();
    case 1:
        return func_ov048_020c3844();
    case 3:
        return func_ov050_020c3b9c();
    case 2:
        return func_ov049_020c4220();
    }
    return NULL;
}
