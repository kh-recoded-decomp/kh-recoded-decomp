#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s32 func_ov031_020bc700(void);
extern BOOL IsWithinPlaneSet_0203ebc8(VecFx32 *point, s32 threshold);

BOOL IsPointInViewDepth_020bd284(VecFx32 *point, s32 threshold) {
    if (point->z < -(threshold + func_ov031_020bc700())) {
        return FALSE;
    }
    return IsWithinPlaneSet_0203ebc8(point, threshold);
}
