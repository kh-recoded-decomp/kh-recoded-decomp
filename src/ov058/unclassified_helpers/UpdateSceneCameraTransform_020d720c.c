#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[8];
    VecFx32 center;
    VecFx32 prevCenter;
} SceneCenterState;

extern SceneCenterState data_ov058_020d8a24;
extern s16 data_0205356c[];

extern u16 func_ov046_020c3074(void);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_01ff9110(const MtxFx33 *src, MtxFx43 *dst);
extern void func_ov046_020c3024(MtxFx43 *mtx);

void UpdateSceneCameraTransform_020d720c(BOOL force)
{
    SceneCenterState *state = &data_ov058_020d8a24;
    BOOL changed = TRUE;
    int index;
    MtxFx43 mtx;
    MtxFx33 rot;

    if (!force && state->center.x == state->prevCenter.x && state->center.y == state->prevCenter.y && state->center.z == state->prevCenter.z) {
        changed = FALSE;
    }
    if (!changed) {
        return;
    }
    index = func_ov046_020c3074() >> 4;
    MTX_RotY33_01ff923c(&rot, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
    func_01ff9110(&rot, &mtx);
    mtx._30 = state->center.x;
    mtx._31 = state->center.y;
    mtx._32 = state->center.z;
    func_ov046_020c3024(&mtx);
}
