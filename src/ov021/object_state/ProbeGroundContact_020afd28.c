#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MotionQuery {
    VecFx32 *origin;
    VecFx32 *motion;
    int mask;
    u16 group;
    u16 layers;
    int ignore;
    u8 work[0x4c];
} MotionQuery;

typedef struct ContactFace {
    u8 pad0[0x14];
    s16 normal[3];
} ContactFace;

typedef struct ContactHit {
    u8 pad0[8];
    ContactFace *face;
    u8 padC[4];
    int isWall;
    u8 pad14[0x18];
    fx32 fraction;
} ContactHit;

extern ContactHit *QueryWorldMotionCollision_02036484(MotionQuery *query);
extern void addScaledVector_020301ac(fx32 scale, const VecFx32 *v, const VecFx32 *base, VecFx32 *out);

BOOL ProbeGroundContact_020afd28(const VecFx32 *position, VecFx32 *motion, VecFx32 *normal, VecFx32 *contact, BOOL floorOnly)
{
    ContactHit *hit;
    BOOL result = FALSE;
    struct {
        VecFx32 origin;
        MotionQuery query;
    } local;

    local.origin = *position;
    local.query.motion = motion;
    local.origin.y += 0x800;
    local.query.origin = &local.origin;
    local.query.mask = 0;
    local.query.group = 0;
    local.query.layers = 0x30;
    local.query.ignore = 0;
    hit = QueryWorldMotionCollision_02036484(&local.query);
    if (hit == NULL) {
        return result;
    }
    if (floorOnly && hit->isWall != 0) {
        return result;
    }
    normal->x = hit->face->normal[0];
    normal->y = hit->face->normal[1];
    normal->z = hit->face->normal[2];
    addScaledVector_020301ac(hit->fraction, local.query.motion, local.query.origin, contact);
    return TRUE;
}
