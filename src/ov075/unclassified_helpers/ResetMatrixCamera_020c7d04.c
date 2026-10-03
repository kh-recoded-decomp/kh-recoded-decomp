#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xd4];
    u32 dirtyFlags;
    u8 pad_0d8[0x218 - 0xd8];
    VecFx32 camPos;
    VecFx32 camUp;
    VecFx32 camTarget;
} CameraState;

extern CameraState data_0205a924;
extern u8 data_0205a92c[];
extern u8 data_0205a970[];
extern void MTX_OrthoW_02005f10(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far, fx32 scaleW,
                                void *projOut);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, void *viewOut);

void ResetMatrixCamera_020c7d04(void)
{
    VecFx32 up;
    VecFx32 target;
    VecFx32 pos;

    MTX_OrthoW_02005f10(0xc0000, 0, 0, 0x100000, 0, 0x400000, 0x200000, data_0205a92c);
    data_0205a924.dirtyFlags &= ~0x50;
    up.z = 0;
    up.x = 0;
    up.y = 0x1000;
    pos.z = 0x400000;
    pos.y = 0;
    pos.x = 0;
    data_0205a924.camPos = pos;
    data_0205a924.camUp = up;
    target.z = 0;
    target.y = 0;
    target.x = 0;
    data_0205a924.camTarget = target;
    func_01ff9b70(&pos, &up, &target, data_0205a970);
    data_0205a924.dirtyFlags &= ~0xe8;
}
