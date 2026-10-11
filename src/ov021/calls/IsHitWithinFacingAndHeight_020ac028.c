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
BOOL IsHitWithinFacingAndHeight_020ac028(HitFacingRecord *record, HitFacingSample *sample,
                               const VecFx32 *position);

extern VecFx32 GetShapeCenter_0203b43c(const void *shape);
extern fx32 VEC_Distance_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

enum {
    HIT_REFERENCE_HORIZONTAL_RANGE = 0x11cd,
    HIT_REFERENCE_HEIGHT_MARGIN = 0x800
};

BOOL IsHitWithinFacingAndHeight_020ac028(HitFacingRecord *record, HitFacingSample *sample,
                               const VecFx32 *position)
{
    if (!IsHitWithinFacingCone_020abfb0(record, sample)) {
        return FALSE;
    }
    if (record->referencePosition != NULL) {
        VecFx32 center = GetShapeCenter_0203b43c(record);
        if (record->referencePosition->y <= center.y) {
            VecFx32 horizontalReference;
            VecFx32 horizontalPosition;
            BOOL nearby = FALSE;

            horizontalReference = *record->referencePosition;
            horizontalPosition = *position;
            horizontalPosition.y = 0;
            horizontalReference.y = 0;
            if (VEC_Distance_01ffa0f4(&horizontalReference, &horizontalPosition) <
                HIT_REFERENCE_HORIZONTAL_RANGE) {
                nearby = TRUE;
            }
            if (nearby && record->referencePosition->y >
                position->y + HIT_REFERENCE_HEIGHT_MARGIN) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
