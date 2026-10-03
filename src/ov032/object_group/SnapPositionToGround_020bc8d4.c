#include "nitro/fx_types.h"

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL ProbeGroundBelow_020bc6fc(const VecFx32 *origin, fx32 length, VecFx32 *hitPoint);

BOOL SnapPositionToGround_020bc8d4(const VecFx32 *offset, const VecFx32 *base, VecFx32 *out, fx32 height)
{
    VecFx32 probe;
    VecFx32 ground;

    VEC_Add_01ff9e0c(offset, base, &probe);
    probe.y += height;
    *out = *base;
    if (ProbeGroundBelow_020bc6fc(&probe, height, &ground)) {
        probe.y -= height;
        if (probe.y < ground.y) {
            out->y += ground.y - probe.y;
            return TRUE;
        }
    }
    return FALSE;
}
