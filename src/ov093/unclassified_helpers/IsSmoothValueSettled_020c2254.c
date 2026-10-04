#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 target;
    fx32 current;
} SmoothValue;

typedef struct {
    u8 pad_0000[0xd1e4];
    SmoothValue smoothValues[2];
} SceneWork;

extern SceneWork *g_sceneWork_020c50e0;

BOOL IsSmoothValueSettled_020c2254(int index)
{
    SmoothValue *value = &g_sceneWork_020c50e0->smoothValues[index];
    fx32 diff = value->target - value->current;
    if (diff < 0) {
        diff = (fx32)(((fx64)diff * -1 + 0x800LL) >> 12);
    }
    return (diff >> 12) < 1;
}
