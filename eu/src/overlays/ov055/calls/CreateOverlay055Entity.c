#include "nitro/types.h"

typedef struct Overlay055Entity {
    u8 opaque[0x1294];
} Overlay055Entity;

extern Overlay055Entity *gOverlay055EntityGlobalStorage;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void InitOverlay055Entity(Overlay055Entity *entity, void *context);
extern void ResetActorCombatState(Overlay055Entity *entity);

Overlay055Entity *CreateOverlay055Entity(void *context)
{
    Overlay055Entity *entity = NNSi_FndAllocFromDefaultHeap(sizeof(Overlay055Entity));

    gOverlay055EntityGlobalStorage = entity;
    InitOverlay055Entity(entity, context);
    ResetActorCombatState(entity);
    return entity;
}
