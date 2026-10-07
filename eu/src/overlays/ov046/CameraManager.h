#ifndef OV046_CAMERA_MANAGER_H
#define OV046_CAMERA_MANAGER_H

#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_000[0x80];
    s32 mode;
    u8 pad_084[0x5C];
    u32 stateFlags;
    u8 pad_0E4[0x10];
    void *focusTarget;
    u8 pad_0F8[0x44];
    u8 embeddedView[1];
} CameraManager;

extern CameraManager *data_ov046_020c3500;

#endif
