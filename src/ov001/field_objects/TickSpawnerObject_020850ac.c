#include "nitro/types.h"

typedef struct SpawnerObject {
    u8 pad_00[0x8];
    void *spawner;
} SpawnerObject;

extern void AdvanceSpawnerTimer_0208502c(void *spawner, SpawnerObject *object);

int TickSpawnerObject_020850ac(SpawnerObject *object)
{
    AdvanceSpawnerTimer_0208502c(object->spawner, object);
    return 0;
}
