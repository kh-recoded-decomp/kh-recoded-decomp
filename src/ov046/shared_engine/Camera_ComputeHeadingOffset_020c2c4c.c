#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CameraOffsetSource {
    VecFx32 position;
    VecFx32 offset;
} CameraOffsetSource;

extern const s16 data_0205356c[];
extern u16 GetBiasAdjustedField_0206dc80(int playerIndex);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

void Camera_ComputeHeadingOffset_020c2c4c(const CameraOffsetSource *source, s32 unused, VecFx32 *out)
{
    MtxFx33 rotation;
    VecFx32 offset;
    int index = GetBiasAdjustedField_0206dc80(0) >> 4;

    MTX_RotY33_01ff923c(&rotation, data_0205356c[(0x400 - index) & 0xfff], data_0205356c[index]);
    if (source != NULL) {
        MTX_MultVec33_01ff9404(&source->offset, &rotation, out);
        return;
    }
    offset = MakeVec(0, 0x1333, 0);
    MTX_MultVec33_01ff9404(&offset, &rotation, out);
}
