#include "nitro/types.h"

typedef struct Ov054Actor Ov054Actor;

extern Ov054Actor *gOv054WorkData;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void InitOverlay054Entity(Ov054Actor *actor, u8 variant);
extern void ResetActorCombatState(Ov054Actor *actor);

Ov054Actor *CreateOv054Actor(u8 variant)
{
    Ov054Actor *actor = NNSi_FndAllocFromDefaultHeap(0x1288);

    gOv054WorkData = actor;
    InitOverlay054Entity(actor, variant);
    ResetActorCombatState(actor);
    return actor;
}
