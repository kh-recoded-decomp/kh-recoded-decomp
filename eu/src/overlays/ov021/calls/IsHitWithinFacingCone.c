#include "src/overlays/ov021/HitFacingFilter.h"

extern const s16 gSinFx12Table[];
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

BOOL IsHitWithinFacingCone(HitFacingRecord *record, HitFacingSample *sample)
{
    VecFx32 direction;
    VecFx32 facing;
    int angle;

    if (record->facingLimit != FX32_ONE &&
        (record->direction.x != 0 || record->direction.z != 0) &&
        (sample->direction.x != 0 || sample->direction.z != 0)) {
        angle = record->yaw >> 4;
        facing.x = -gSinFx12Table[angle];
        facing.y = 0;
        facing.z = -gSinFx12Table[(0x400 - angle) & 0xfff];
        direction.x = sample->direction.x;
        direction.z = sample->direction.z;
        direction.y = 0;
        if (VEC_DotProduct(&direction, &facing) < -record->facingLimit) {
            return FALSE;
        }
    }
    return TRUE;
}
