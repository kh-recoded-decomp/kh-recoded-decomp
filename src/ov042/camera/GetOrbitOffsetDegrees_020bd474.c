#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 GetCameraOrbitOffset_020af8d4(fx32 radians);

void GetOrbitOffsetDegrees_020bd474(VecFx32 *out, int degrees) {
    *out = GetCameraOrbitOffset_020af8d4((fx32)((s64)degrees * 0x3244 / 0xb4000));
}
