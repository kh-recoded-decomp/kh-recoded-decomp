#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorMover {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
} ActorMover;

extern void *GetActorById_02036240(u32 id);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);

void SetActorTargetPosition_02083c04(ActorMover *mover, const VecFx32 *position)
{
    mover->position = *position;
    Obj_SetPosition_0203569c(GetActorById_02036240(mover->actorId), &mover->position);
}
