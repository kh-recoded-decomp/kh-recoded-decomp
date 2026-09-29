#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x78];
    fx32 timeScale;
} TimedObject;

void SetObjectTimeScale_020d8230(void *list, TimedObject *object, fx32 timeScale)
{
    object->timeScale = timeScale;
}
