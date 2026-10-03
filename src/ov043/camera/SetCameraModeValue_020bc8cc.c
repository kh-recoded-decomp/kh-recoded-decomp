#include "nitro/types.h"

typedef struct {
    u8 _0[0x40];
    int mode;
} CameraState;

extern CameraState *data_ov043_020bd2c0;

void SetCameraModeValue_020bc8cc(int mode) {
    CameraState *camera = data_ov043_020bd2c0;
    if (camera->mode != mode) {
        camera->mode = mode;
    }
}
