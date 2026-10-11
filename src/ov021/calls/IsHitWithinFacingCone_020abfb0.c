#include "nitro/fx.h"

typedef struct HitFacingRecord {
    u8 pad00[0x48];
    VecFx32 direction;
    fx32 facingLimit;
    u16 yaw;
    u8 pad5a[2];
    const VecFx32 *referencePosition;
} HitFacingRecord;

typedef struct HitFacingSample {
    fx32 distance;
    VecFx32 direction;
} HitFacingSample;

BOOL IsHitWithinFacingCone_020abfb0(HitFacingRecord *record, HitFacingSample *sample);
BOOL IsHitWithinFacingAndHeight(HitFacingRecord *record, HitFacingSample *sample,
                               const VecFx32 *position);

extern const s16 gSinFx12Table_0205356c[];
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

BOOL IsHitWithinFacingCone_020abfb0(HitFacingRecord *record, HitFacingSample *sample)
{
    VecFx32 direction;
    VecFx32 facing;
    int angle;

    if (record->facingLimit != FX32_ONE &&
        (record->direction.x != 0 || record->direction.z != 0) &&
        (sample->direction.x != 0 || sample->direction.z != 0)) {
        angle = record->yaw >> 4;
        facing.x = -gSinFx12Table_0205356c[angle];
        facing.y = 0;
        facing.z = -gSinFx12Table_0205356c[(0x400 - angle) & 0xfff];
        direction.x = sample->direction.x;
        direction.z = sample->direction.z;
        direction.y = 0;
        if (VEC_DotProduct_01ff9e6c(&direction, &facing) < -record->facingLimit) {
            return FALSE;
        }
    }
    return TRUE;
}
