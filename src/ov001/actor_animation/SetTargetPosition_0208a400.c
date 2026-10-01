#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldActor {
    u8 pad_000[0x840];
    VecFx32 targetPosition;
    u8 pad_84C[0xc];
    int targetParam;
    int targetFlags;
} FieldActor;

void SetTargetPosition_0208a400(FieldActor *actor, const VecFx32 *position, int param, int flags)
{
    actor->targetPosition = *position;
    actor->targetParam = param;
    actor->targetFlags = flags;
}
