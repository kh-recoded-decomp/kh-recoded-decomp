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

extern Ov042CameraState *data_ov042_020be5e0;
#define gOv042CameraState data_ov042_020be5e0

#endif
