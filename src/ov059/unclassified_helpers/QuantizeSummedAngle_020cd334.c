#include "nitro/types.h"

extern u16 func_ov021_020a7544(void *angles);
extern u16 AddQuantizedViewAngle_020cd2c4(u16 angle);

u16 QuantizeSummedAngle_020cd334(void *angles)
{
    return AddQuantizedViewAngle_020cd2c4(func_ov021_020a7544(angles) + 0x3fff);
}
