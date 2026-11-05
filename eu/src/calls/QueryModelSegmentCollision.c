#include "src/collision/CollisionQueries.h"

extern CollisionResult *QueryModelCollision(CollisionScene *scene, void *params);

CollisionResult *QueryModelSegmentCollision(CollisionScene *scene,
                                           MoverCastParams *params)
{
    params->radius = 0;
    return QueryModelCollision(scene, params);
}
