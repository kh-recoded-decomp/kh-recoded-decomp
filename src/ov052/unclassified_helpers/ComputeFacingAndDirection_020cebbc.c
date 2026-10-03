#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s16 data_0205356c[];
extern u32 func_ov001_0206db78(u32 index);
extern u32 func_ov021_020a7544(u32 entry);
extern int func_ov052_020cec00(int entity, int angle);

int ComputeFacingAndDirection_020cebbc(int entity, VecFx32 *out)
{
    int angle = func_ov052_020cec00(entity, func_ov021_020a7544(func_ov001_0206db78(*(u8 *)(entity + 0x9b4))));
    if (out != NULL) {
        int index = angle >> 4;
        out->x = -data_0205356c[index];
        out->z = -data_0205356c[(0x400 - index) & 0xfff];
    }
    return angle;
}
