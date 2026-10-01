#include "nitro/types.h"

typedef struct StageActor StageActor;

typedef struct StageOwner {
    u8 pad_000[0x3b2];
    u16 linkedActorId;
} StageOwner;

extern StageActor *GetStageActor_0209c040(int id);

StageActor *GetLinkedStageActor_0209c2f0(StageOwner *owner)
{
    if (owner->linkedActorId == 0) {
        return NULL;
    }
    return GetStageActor_0209c040((s16)owner->linkedActorId);
}
