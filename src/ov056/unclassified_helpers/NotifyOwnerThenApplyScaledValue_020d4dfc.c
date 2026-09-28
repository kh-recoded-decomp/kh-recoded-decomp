#include "nitro/types.h"

typedef struct Actor Actor;

typedef struct {
    u8 pad_000[0x200];
    void (*onEvent)(void *owner, u32 eventId);
} OwnerEntity;

extern OwnerEntity *GetBoundedEntryField_0206db5c(u32 handle);
extern void ComputeAndApplyLevelScaledValue_020d4d5c(Actor *actor, u32 handle);

void NotifyOwnerThenApplyScaledValue_020d4dfc(Actor *actor, u32 handle)
{
    OwnerEntity *owner = GetBoundedEntryField_0206db5c(handle);

    if (owner->onEvent != NULL) {
        owner->onEvent(owner, 0);
    }
    ComputeAndApplyLevelScaledValue_020d4d5c(actor, handle);
}
