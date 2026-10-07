#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitInfo HitInfo;
typedef struct MoveActor MoveActor;

typedef HitInfo *(*GroundProbe)(MoveActor *actor, VecFx32 *position, VecFx32 *delta, VecFx32 *hitPosition);

typedef struct MoveCallbacks {
    u8 pad_00[0x20];
    GroundProbe probeGround;
} MoveCallbacks;

struct MoveActor {
    u8 pad_000[0x278];
    MoveCallbacks *callbacks;
};

HitInfo *InvokeActorGroundProbe_02091658(MoveActor *actor, VecFx32 *position, VecFx32 *delta, VecFx32 *hitPosition)
{
    GroundProbe callback = actor->callbacks->probeGround;

    if (callback != NULL) {
        return callback(actor, position, delta, hitPosition);
    }
    return NULL;
}
