#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[4];
    void *pool;
    u8 pad_08[0x52];
    u16 flags;
    s16 prevIndex;
} Actor;

extern BOOL IsDestroyed_020a31f8(Actor *self);
extern Actor *func_ov001_0208635c(void *pool, int index);

Actor *FindFirstLiveLink_020a2128(Actor *actor)
{
    Actor *result = NULL;
    while (1) {
        if (!IsDestroyed_020a31f8(actor)) {
            result = actor;
        }
        if (actor->prevIndex < 0) {
            break;
        }
        actor = func_ov001_0208635c(actor->pool, actor->prevIndex);
    }
    return result;
}
