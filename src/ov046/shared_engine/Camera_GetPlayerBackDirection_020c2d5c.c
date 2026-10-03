#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const s16 data_0205356c[];
extern u16 GetBiasAdjustedField_0206dc80(int playerIndex);

void Camera_GetPlayerBackDirection_020c2d5c(VecFx32 *out)
{
    int index = GetBiasAdjustedField_0206dc80(0) >> 4;

    out->y = 0;
    out->x = -data_0205356c[index];
    out->z = -data_0205356c[(0x400 - index) & 0xfff];
}
