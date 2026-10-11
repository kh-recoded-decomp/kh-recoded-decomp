#include "nitro/fx_types.h"

typedef struct CollisionQuery {
    VecFx32 *origin;
    VecFx32 *delta;
    u32 mask;
    u16 flags;
    u16 layerMask;
    void *filter;
    u8 reserved14[0x4c];
} CollisionQuery;

typedef struct CollisionHit {
    u32 reserved00;
    void *surface;
    u8 reserved08[0x24];
    fx32 fraction;
} CollisionHit;

extern CollisionHit *ResetAndQueryWorldCollision(CollisionQuery *query);
extern void AddScaledVector(fx32 scale, const VecFx32 *vector, const VecFx32 *base, VecFx32 *result);

BOOL QueryStageFloor(VecFx32 *position, VecFx32 *floorPoint)
{
    CollisionQuery query;
    VecFx32 origin = *position;
    VecFx32 down;
    CollisionHit *hit;

    down.x = 0;
    down.y = -0xe000;
    down.z = 0;
    query.origin = &origin;
    query.delta = &down;
    query.mask = 0;
    query.flags = 0;
    query.layerMask = 0x7f;
    query.filter = NULL;
    hit = ResetAndQueryWorldCollision(&query);
    if (hit != NULL && hit->surface != NULL) {
        AddScaledVector(hit->fraction, &down, &origin, floorPoint);
        return TRUE;
    }
    floorPoint->y = 0;
    return FALSE;
}
