#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 *func_ov001_0206dc4c(int index);
extern BOOL ProbeGroundBelow_020bc6fc(const VecFx32 *origin, fx32 length, VecFx32 *hitPoint);

BOOL FindLevelCellCenter_020beeb8(int cell, VecFx32 *out)
{
    VecFx32 center;
    VecFx32 corners[4];
    fx32 left;
    fx32 right;
    fx32 far;
    BOOL result = FALSE;
    VecFx32 *pos = func_ov001_0206dc4c(0);
    fx32 near;
    int i;
    fx32 height;

    center.x = (cell % 16) * 0x1800 - 0xc000;
    center.y = 0x1e000;
    center.z = (cell / 16) * 0x1800 - 0xc000;
    if (center.x - 0xc00 <= pos->x && pos->x <= center.x + 0xc00 && center.z - 0xc00 <= pos->z && pos->z <= center.z + 0xc00) {
        return result;
    }
    far = center.z + 0xc00;
    near = center.z - 0xc00;
    height = center.y;
    left = center.x - 0xc00;
    i = 0;
    right = center.x + 0xc00;
    for (; (u32)i < 4; i++) {
        pos = &corners[i];
        if (i & 1) {
            pos->x = right;
        } else {
            pos->x = left;
        }
        if (i / 2) {
            pos->z = far;
        } else {
            pos->z = near;
        }
        pos->y = height;
        if (!ProbeGroundBelow_020bc6fc(pos, 0xc00, pos)) {
            return FALSE;
        }
        if (i > 0 && pos->y != pos[-1].y) {
            return FALSE;
        }
    }
    center.y = corners[0].y;
    *out = center;
    return TRUE;
}
