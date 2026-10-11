#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const s16 data_0205356c[];

extern void RotateVectorAroundAxis_0204b34c(VecFx32 *vec, const VecFx32 *axis, s32 angle);

#define DEG_TO_INDEX(deg) ((int)(u16)((((s64)(deg) << 16) / 0x168000) & 0xffff) >> 4)
#define SIN_AT(index) data_0205356c[index]
#define COS_AT(index) data_0205356c[(0x400 - (index)) & 0xfff]
#define FX_MUL(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))

void ComputePanelAxesFromAngles_020d0728(const VecFx32 *angles, VecFx32 *forward, VecFx32 *up)
{
    int pitch = DEG_TO_INDEX(angles->x);
    int yaw = DEG_TO_INDEX(angles->y);
    fx32 cosPitch = COS_AT(pitch);
    fx32 sinPitch = SIN_AT(pitch);
    fx32 sinYaw = SIN_AT(yaw);
    fx32 cosYaw = COS_AT(yaw);
    int raised;
    fx32 cosRaised;

    forward->x = -FX_MUL(cosPitch, cosYaw);
    forward->z = -FX_MUL(sinPitch, cosYaw);
    forward->y = -sinYaw;
    raised = DEG_TO_INDEX(((const fx32 *)angles)[1] + 0x5a000);
    cosRaised = COS_AT(raised);
    up->x = FX_MUL(cosPitch, cosRaised);
    up->y = SIN_AT(raised);
    up->z = FX_MUL(sinPitch, cosRaised);
    RotateVectorAroundAxis_0204b34c(up, forward, (s64)-angles->z * 0x3244 / 0xb4000);
}

