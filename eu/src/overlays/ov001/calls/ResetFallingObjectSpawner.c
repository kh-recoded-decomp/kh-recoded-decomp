#include "nitro/types.h"

typedef struct FallingObjectDefinition {
    u8 pad_00[8];
    u16 flags;
} FallingObjectDefinition;

typedef struct FallingObjectState {
    u8 pad_00[0xc];
    FallingObjectDefinition *definition;
    u8 pad_10[4];
    int (*update)(struct FallingObjectState *object);
    u8 pad_18[0x20];
    u8 actorIndex;
    u8 pad_39[0x15];
    u16 flags;
    u8 pad_50[8];
    int timer;
} FallingObjectState;

extern int TickSpawnerObject(FallingObjectState *object);
extern void ActorSlot_SetFlag8ByIndex(int actorIndex, BOOL enabled);

void ResetFallingObjectSpawner(FallingObjectState *object)
{
    object->timer = 0;
    object->update = TickSpawnerObject;
    object->flags &= ~0x20;
    if (object->definition->flags & 1) {
        ActorSlot_SetFlag8ByIndex(object->actorIndex, FALSE);
    }
}
