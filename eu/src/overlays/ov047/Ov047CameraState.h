#ifndef KH_RECODED_OV047_CAMERA_STATE_H
#define KH_RECODED_OV047_CAMERA_STATE_H

#include "nitro/types.h"

typedef struct Ov047CameraState {
    u8 pad_000[0x258];
    u8 trackingController[1];
} Ov047CameraState;

extern Ov047CameraState *data_ov036_020c3500;
#define gOv047CameraState data_ov036_020c3500

#endif
