#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

fx32 FixedPointLerp_0208f884(fx32 start, fx32 end, fx32 t)
{
    return start + FixedPointMultiply12(end - start, t);
}
