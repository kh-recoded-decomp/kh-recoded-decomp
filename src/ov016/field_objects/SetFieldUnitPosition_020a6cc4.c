#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x30];
    u16 flags;
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
} FieldUnit;

extern void *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(void *actor, const VecFx32 *position);
extern void func_ov016_020a2598(FieldUnit *unit, int arg);

void SetFieldUnitPosition_020a6cc4(FieldUnit *unit, const VecFx32 *position)
{
    unit->position = *position;
    Obj_SetPosition_0203569c(func_02036240(unit->actorId), &unit->position);
    if (unit->flags & 4) {
        func_ov016_020a2598(unit, 0);
    }
}
