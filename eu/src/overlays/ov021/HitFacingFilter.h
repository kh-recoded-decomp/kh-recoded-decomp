#ifndef OV021_HIT_FACING_FILTER_H
#define OV021_HIT_FACING_FILTER_H

#include "nitro/fx.h"

/* Facing-filter view of an attack shape. The preceding shape fields are
 * handled by the collision routines rather than this filter. */
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

BOOL IsHitWithinFacingCone(HitFacingRecord *record, HitFacingSample *sample);
BOOL IsHitWithinFacingAndHeight(HitFacingRecord *record, HitFacingSample *sample,
                               const VecFx32 *position);

#endif
