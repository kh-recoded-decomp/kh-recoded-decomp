#include "nitro/types.h"

typedef struct Actor Actor;

extern Actor *gActorWork;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void Actor_InitVariantCallbacks(Actor *actor, u8 variant);
extern void Actor_Init(Actor *actor);

Actor *Actor_Create(u8 variant)
{
    Actor *actor = NNSi_FndAllocFromDefaultHeap(0x1830);

    gActorWork = actor;
    Actor_InitVariantCallbacks(actor, variant);
    Actor_Init(actor);
    return actor;
}
