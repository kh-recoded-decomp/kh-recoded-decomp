#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 *func_ov001_0206dc4c(int index);
extern VecFx32 *func_ov021_020af5b4(void);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FixedPointMultiply12(fx32 left, fx32 right);
extern BOOL ScanActorsForSideTarget_0206b25c(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern BOOL ScanObjectsForSideTarget_0206b2c0(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern BOOL ScanRecordSlotsForSideTarget_0206b334(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);

BOOL FindSideTarget_0206b1ac(s32 direction, const VecFx32 *position, fx32 *limit)
{
    BOOL found = FALSE;
    VecFx32 *playerPos;
    fx32 bound;
    fx32 offset;
    fx32 nextOffset;
    VecFx32 facing;
    VecFx32 delta;

    playerPos = func_ov001_0206dc4c(0);
    VEC_Subtract_01ff9e3c(playerPos, func_ov021_020af5b4(), &facing);
    VEC_Subtract_01ff9e3c(position, playerPos, &delta);
    offset = FixedPointMultiply12(delta.x, facing.z) - FixedPointMultiply12(delta.z, facing.x);
    if (limit == NULL) {
        if (direction == 0x200) {
            bound = 0x7fffffff;
        } else {
            bound = 0x80000000;
        }
    } else {
        bound = *limit;
    }
    if (ScanActorsForSideTarget_0206b25c(&facing, offset, bound, direction, &nextOffset)) {
        bound = nextOffset;
        found = TRUE;
    }
    if (ScanObjectsForSideTarget_0206b2c0(&facing, offset, bound, direction, &nextOffset)) {
        bound = nextOffset;
        found = TRUE;
    }
    if (ScanRecordSlotsForSideTarget_0206b334(&facing, offset, bound, direction, &nextOffset)) {
        bound = nextOffset;
        found = TRUE;
    }
    if (limit != NULL) {
        *limit = bound;
    }
    return found;
}
