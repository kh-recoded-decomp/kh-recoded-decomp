#ifndef RECODED_CAMERA_STATE_H
#define RECODED_CAMERA_STATE_H

#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct CameraGlobalState {
    u32 reserved00[2];
    MtxFx44 projection;
    u32 reserved48;
    MtxFx43 camera;
    u8 reserved7c[0x58];
    u32 flags;
    u8 reservedD8[0x140];
    VecFx32 position;
    VecFx32 up;
    VecFx32 target;
} CameraGlobalState;

typedef struct CameraBackup {
    VecFx32 target;
    VecFx32 position;
    VecFx32 up;
    MtxFx44 projection;
    MtxFx43 camera;
} CameraBackup;

typedef char CameraBackupMustBe148Bytes[sizeof(CameraBackup) == 148 ? 1 : -1];
typedef char CameraProjectionMustStartAt36Bytes[
    (u32)&((CameraBackup *)0)->projection == 36 ? 1 : -1];
typedef char CameraMatrixMustStartAt100Bytes[
    (u32)&((CameraBackup *)0)->camera == 100 ? 1 : -1];
typedef char CameraFlagsMustStartAt212Bytes[
    (u32)&((CameraGlobalState *)0)->flags == 212 ? 1 : -1];
typedef char CameraPositionMustStartAt536Bytes[
    (u32)&((CameraGlobalState *)0)->position == 536 ? 1 : -1];

extern CameraGlobalState NNS_G3dGlb;
extern CameraBackup gSavedCameraState;

extern void func_01ff9b70(const VecFx32 *position, const VecFx32 *up,
                        const VecFx32 *target, MtxFx43 *matrix);
int BeginOrthographicCamera(void);

#endif
