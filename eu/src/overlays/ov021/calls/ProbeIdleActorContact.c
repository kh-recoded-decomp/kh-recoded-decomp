#include "nitro/types.h"

/* Only the flags consulted by this callback are described here. */
typedef struct ContactActorState {
    u8 pad00[0x24];
    u16 reserved : 4;
    u16 attacking : 1;
    u16 flags : 11;
} ContactActorState;

typedef struct ActorContactResult {
    u32 flags;
    s32 kind;
} ActorContactResult;

extern BOOL IsObjectIdle(ContactActorState *object);
extern BOOL ProbeActorContact(int actorId, void *shape, ActorContactResult *result);

BOOL ProbeIdleActorContact(int actorId, void *shape, ContactActorState *object,
                          ActorContactResult *result)
{
    BOOL idle = TRUE;

    if (object != NULL) {
        BOOL wasAttacking = object->attacking;
        object->attacking = 0;
        idle = IsObjectIdle(object);
        object->attacking = (u16)wasAttacking;
    }
    if (ProbeActorContact(actorId, shape, result)) {
        switch (result->kind) {
        default:
            if (result->kind == 1 && idle) {
                result->flags |= 1;
            }
            break;
        case 4:
        case 5:
            result->flags |= 1;
            break;
        }
    }
    return TRUE;
}
