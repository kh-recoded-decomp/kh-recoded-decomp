#include "src/collision/CollisionGeometry.h"

/* Extend the leading face of each axis; source and output may be the same box. */
void OffsetBoxByDelta(const CollisionBounds *source, CollisionBounds *out,
                      const VecFx32 *delta)
{
    if (delta->x > 0) {
        out->max.x = source->max.x + delta->x;
        out->min.x = source->min.x;
    } else {
        out->min.x = source->min.x + delta->x;
        out->max.x = source->max.x;
    }
    if (delta->y > 0) {
        out->max.y = source->max.y + delta->y;
        out->min.y = source->min.y;
    } else {
        out->min.y = source->min.y + delta->y;
        out->max.y = source->max.y;
    }
    if (delta->z > 0) {
        out->max.z = source->max.z + delta->z;
        out->min.z = source->min.z;
    } else {
        out->min.z = source->min.z + delta->z;
        out->max.z = source->max.z;
    }
}
