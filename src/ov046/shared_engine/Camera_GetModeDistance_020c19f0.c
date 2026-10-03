#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraModeParams {
    fx32 pitch;
    fx32 height;
    fx32 distance;
} CameraModeParams;

extern CameraModeParams data_ov046_020c33b0[];
extern VecFx32 *Camera_GetFocusPosition_020c1780(void);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 FixedPointMultiply12(fx32 left, fx32 right);

fx32 Camera_GetModeDistance_020c19f0(int mode)
{
    fx32 distance = data_ov046_020c33b0[mode].distance;

    if (mode != 0) {
        if (mode != 10) {
            goto done;
        }
        if (Camera_GetFocusPosition_020c1780()->z >= -0x10000) {
            goto done;
        }
        distance -= FixedPointMultiply12(distance - data_ov046_020c33b0[0].distance,
                                         FX_Div_01ff9c84(-0x10000 - Camera_GetFocusPosition_020c1780()->z, 0x8000));
    }
    distance += 0x4cd;
done:
    return distance;
}
