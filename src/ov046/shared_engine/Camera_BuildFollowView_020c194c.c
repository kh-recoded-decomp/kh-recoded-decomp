#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0xe4];
    int mode;
} CameraManager;

typedef struct CameraView CameraView;

extern CameraManager *g_cameraManager_020c34e0;
extern const s16 data_0205356c[];
extern int GetBiasAdjustedField_0206dc80(int playerIndex);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void func_ov046_020c179c(CameraView *view, u16 heading);

void Camera_BuildFollowView_020c194c(CameraView *view)
{
    int heading;
    int index;

    if (g_cameraManager_020c34e0->mode != 0x13 && g_cameraManager_020c34e0->mode != 0x15) {
        heading = GetBiasAdjustedField_0206dc80(0);
    } else {
        heading = 0;
    }
    index = (u16)heading >> 4;
    func_ov046_020c179c(view, FixedPointAtan2_020062bc(-data_0205356c[(0x400 - index) & 0xfff], -data_0205356c[index]));
}
