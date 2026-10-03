#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x150];
    VecFx32 velocity;
} FieldActor;

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
} FieldUnit;

extern FieldActor *func_02036240(u32 actorId);

BOOL GetFieldUnitVelocity_020a5340(FieldUnit *unit, VecFx32 *out)
{
    FieldActor *actor = func_02036240(unit->actorId);

    *out = actor->velocity;
    if (actor->velocity.x != 0 || actor->velocity.y != 0 || actor->velocity.z != 0) {
        return TRUE;
    }
    return FALSE;
}
