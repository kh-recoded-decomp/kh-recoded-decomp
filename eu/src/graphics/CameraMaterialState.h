#ifndef RECODED_CAMERA_MATERIAL_STATE_H
#define RECODED_CAMERA_MATERIAL_STATE_H

#include "nitro/types.h"
#include "nitro/fx.h"

/* View of the SDK global state beginning at its material-color parameters. */
typedef struct CameraMaterialStateView {
    u8 reserved00[0x54];
    u32 dirtyFlags;
    u8 reserved58[0x198 - 0x58];
    VecFx32 position;
    VecFx32 up;
    VecFx32 target;
} CameraMaterialStateView;

typedef char CameraDirtyFlagsOffsetCheck[
    (u32)&((CameraMaterialStateView *)0)->dirtyFlags == 0x54 ? 1 : -1];
typedef char CameraPositionOffsetCheck[
    (u32)&((CameraMaterialStateView *)0)->position == 0x198 ? 1 : -1];

extern CameraMaterialStateView NNS_G3dGlb_prmMatColor0;
extern MtxFx44 NNS_G3dGlb_projMtx;
extern MtxFx43 NNS_G3dGlb_cameraMtx;
extern void MTX_OrthoW(fx32 top, fx32 bottom, fx32 left, fx32 right,
                      fx32 nearPlane, fx32 farPlane, fx32 scaleW, MtxFx44 *projection);
extern void func_01ff9b70(const VecFx32 *position, const VecFx32 *up,
                        const VecFx32 *target, MtxFx43 *view);

#endif
