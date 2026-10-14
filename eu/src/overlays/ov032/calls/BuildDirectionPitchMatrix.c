#pragma opt_lifetimes off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct DirectionMatrix {
    VecFx32 forward;
    VecFx32 up;
    VecFx32 right;
} DirectionMatrix;

extern s16 gSinFx12Table[4096];
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern fx32 FX_Mul(fx32 first, fx32 second);
extern void VEC_CrossProduct(const VecFx32 *first, const VecFx32 *second, VecFx32 *result);

static inline fx16 SinDirectionIndex(long index)
{
    return gSinFx12Table[index];
}

static inline fx16 CosDirectionIndex(long index)
{
    return gSinFx12Table[(1024 - index) & 4095];
}

void BuildDirectionPitchMatrix(DirectionMatrix *matrix, const VecFx32 *direction, int pitch)
{
    VecFx32 forward;
    VecFx32 up;
    VecFx32 right;
    int heading = FX_Atan2Idx(direction->z, direction->x);
    int pitchIndex;
    long pitchCos;
    long headingCos;
    long headingSin;

    pitch = (u16)pitch;
    pitchIndex = pitch >> 4;
    heading >>= 4;
    pitchCos = CosDirectionIndex(pitchIndex);
    headingCos = CosDirectionIndex(heading);
    forward.x = FX_Mul(headingCos, pitchCos);
    forward.y = SinDirectionIndex(pitchIndex);
    headingSin = SinDirectionIndex(heading);
    forward.z = FX_Mul(headingSin, pitchCos);
    pitch = (u16)(pitch + 0x4000);
    pitchIndex = pitch >> 4;
    pitchCos = CosDirectionIndex(pitchIndex);
    up.x = FX_Mul(headingCos, pitchCos);
    up.y = SinDirectionIndex(pitchIndex);
    up.z = FX_Mul(headingSin, pitchCos);
    VEC_CrossProduct(&forward, &up, &right);
    matrix->forward.x = forward.x;
    matrix->forward.y = forward.y;
    matrix->forward.z = forward.z;
    matrix->up.x = up.x;
    matrix->up.y = up.y;
    matrix->up.z = up.z;
    matrix->right.x = right.x;
    matrix->right.y = right.y;
    matrix->right.z = right.z;
}
