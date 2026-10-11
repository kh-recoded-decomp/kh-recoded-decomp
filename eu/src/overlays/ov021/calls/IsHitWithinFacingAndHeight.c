#include "src/overlays/ov021/HitFacingFilter.h"

extern VecFx32 GetShapeCenter(const void *shape);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

enum {
    HIT_REFERENCE_HORIZONTAL_RANGE = 0x11cd,
    HIT_REFERENCE_HEIGHT_MARGIN = 0x800
};

BOOL IsHitWithinFacingAndHeight(HitFacingRecord *record, HitFacingSample *sample,
                               const VecFx32 *position)
{
    if (!IsHitWithinFacingCone(record, sample)) {
        return FALSE;
    }
    if (record->referencePosition != NULL) {
        VecFx32 center = GetShapeCenter(record);
        if (record->referencePosition->y <= center.y) {
            VecFx32 horizontalReference;
            VecFx32 horizontalPosition;
            BOOL nearby = FALSE;

            horizontalReference = *record->referencePosition;
            horizontalPosition = *position;
            horizontalPosition.y = 0;
            horizontalReference.y = 0;
            if (VEC_Distance(&horizontalReference, &horizontalPosition) <
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
