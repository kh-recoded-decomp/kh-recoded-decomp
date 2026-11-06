#include "nitro/types.h"

typedef struct Overlay057Entity {
    u8 opaque[0x1294];
} Overlay057Entity;

extern Overlay057Entity *gOverlay057EntityGlobalStorage;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void InitOverlay057Entity(Overlay057Entity *entity, void *context);
extern void ResetActorCombatState(Overlay057Entity *entity);

Overlay057Entity *CreateOverlay057Entity(void *context)
{
    Overlay057Entity *entity = NNSi_FndAllocFromDefaultHeap(sizeof(Overlay057Entity));

    gOverlay057EntityGlobalStorage = entity;
    InitOverlay057Entity(entity, context);
    ResetActorCombatState(entity);
    return entity;
}
