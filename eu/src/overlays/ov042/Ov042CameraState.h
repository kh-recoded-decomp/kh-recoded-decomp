#ifndef KH_RECODED_OV042_CAMERA_STATE_H
#define KH_RECODED_OV042_CAMERA_STATE_H

#include "nitro/fx_types.h"

typedef struct Ov042CameraState {
    u8 pad_000[0x40];
    u32 colliderRegistrationMode;
    u32 previousColliderRegistrationMode;
    u8 pad_048[8];
    u32 modeStatus;
    /* Four native fx32 bounds, in the order returned by GetCameraFrustumBounds. */
    fx32 frustumBounds[4];
    u8 pad_064[0xac];
    VecFx32 goalPosition;
    VecFx32 colliderOffset;
} Ov042CameraState;

typedef char Ov042ColliderModePosition[(u32)&((Ov042CameraState *)0)->colliderRegistrationMode == 0x40 ? 1 : -1];
typedef char Ov042FrustumBoundsPosition[(u32)&((Ov042CameraState *)0)->frustumBounds == 0x54 ? 1 : -1];
typedef char Ov042ColliderOffsetPosition[(u32)&((Ov042CameraState *)0)->colliderOffset == 0x11c ? 1 : -1];

extern Ov042CameraState *gCameraSceneGlobalStorage;
#define gOv042CameraState gCameraSceneGlobalStorage
void SetCameraColliderOffsetAngle(fx32 degrees);

#endif
