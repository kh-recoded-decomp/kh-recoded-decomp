#ifndef KH_RECODED_OV042_CAMERA_STATE_H
#define KH_RECODED_OV042_CAMERA_STATE_H

#include "nitro/fx_types.h"

typedef struct Ov042CameraState {
    u8 pad_000[0x50];
    u32 modeStatus;
    u8 pad_054[0xbc];
    VecFx32 goalPosition;
    VecFx32 colliderOffset;
} Ov042CameraState;

typedef char Ov042ColliderOffsetPosition[(u32)&((Ov042CameraState *)0)->colliderOffset == 0x11c ? 1 : -1];

extern Ov042CameraState *data_ov042_020be5e0;
#define gOv042CameraState data_ov042_020be5e0
void SetCameraColliderOffsetAngle(fx32 degrees);

#endif
