#ifndef KH_RECODED_OV043_CAMERA_STATE_H
#define KH_RECODED_OV043_CAMERA_STATE_H

#include "nitro/types.h"

typedef struct Ov043CameraState {
    u8 pad_000[0x38];
    u32 flags;
    u8 pad_03c[0xc0];
    u8 activeController;
    u8 pad_0fd[0x0b];
    u8 viewState;
} Ov043CameraState;

extern Ov043CameraState *gOv043CameraState;

#endif
