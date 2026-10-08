#include "nitro/types.h"

typedef struct Ov053Actor Ov053Actor;

extern Ov053Actor *gOv053WorkData;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void InitOverlay053Entity(Ov053Actor *actor, u8 variant);
extern void ResetActorCombatState(Ov053Actor *actor);

Ov053Actor *CreateOv053Actor(u8 variant)
{
    Ov053Actor *actor = NNSi_FndAllocFromDefaultHeap(0x1260);

    gOv053WorkData = actor;
    InitOverlay053Entity(actor, variant);
    ResetActorCombatState(actor);
    return actor;
}
