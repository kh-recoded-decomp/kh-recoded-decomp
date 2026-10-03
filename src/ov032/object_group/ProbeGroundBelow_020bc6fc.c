#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x2c];
    fx32 hitRatio;
} RayHit;

typedef struct {
    const VecFx32 *origin;
    VecFx32 *direction;
    fx32 length;
    u16 mode;
    u16 flags;
    int filter;
    u8 pad_14[0x4c];
} RayQuery;

extern const VecFx32 data_ov032_020bff8c;
extern void *func_02036230(void);
extern RayHit *func_020351b8(void *world, RayQuery *query);
extern void addScaledVector_020301ac(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);

BOOL ProbeGroundBelow_020bc6fc(const VecFx32 *origin, fx32 length, VecFx32 *hitPoint)
{
    VecFx32 direction = data_ov032_020bff8c;
    RayQuery query;
    RayHit *hit;

    query.origin = origin;
    query.direction = &direction;
    query.length = length;
    query.mode = 1;
    query.flags = 0;
    query.filter = 0;
    hit = func_020351b8(func_02036230(), &query);
    if (hit != NULL) {
        addScaledVector_020301ac(hit->hitRatio, query.direction, origin, hitPoint);
        return TRUE;
    }
    return FALSE;
}
