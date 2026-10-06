#include "nitro/types.h"

typedef struct SpawnerObject {
    u8 pad_00[0x8];
    void *spawner;
} SpawnerObject;

extern void AdvanceSpawnerTimer(void *spawner, SpawnerObject *object);

int TickSpawnerObject(SpawnerObject *object)
{
    AdvanceSpawnerTimer(object->spawner, object);
    return 0;
}
