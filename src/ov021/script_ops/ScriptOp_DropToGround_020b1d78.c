#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ScriptContext {
    u8 pad0[0x34];
    VecFx32 position;
} ScriptContext;

typedef struct GroundQuery {
    VecFx32 *origin;
    VecFx32 *ray;
    int mask;
    u16 group;
    u16 layers;
    int ignore;
    u8 work[0x4c];
} GroundQuery;

typedef struct GroundHit {
    u8 pad0[4];
    int hit;
    u8 pad8[0x24];
    fx32 fraction;
} GroundHit;

extern GroundHit *ResetAndQueryWorldCollision_0203644c(GroundQuery *query);
extern void addScaledVector_020301ac(fx32 scale, const VecFx32 *v, const VecFx32 *base, VecFx32 *out);

int ScriptOp_DropToGround_020b1d78(ScriptContext *context)
{
    GroundQuery query;
    VecFx32 origin;
    VecFx32 ray;
    GroundHit *hit;

    origin = context->position;
    origin.y += FX32_ONE;
    ray.x = 0;
    ray.y = -0xe000;
    ray.z = 0;
    query.origin = &origin;
    query.ray = &ray;
    query.mask = 0;
    query.group = 0;
    query.layers = 0x7f;
    query.ignore = 0;
    hit = ResetAndQueryWorldCollision_0203644c(&query);
    if (hit != NULL && hit->hit != 0) {
        addScaledVector_020301ac(hit->fraction, &ray, &origin, &context->position);
    } else {
        context->position.y = 0;
    }
    return 0;
}
