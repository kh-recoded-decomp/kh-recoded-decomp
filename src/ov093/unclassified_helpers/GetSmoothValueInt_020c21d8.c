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

int GetSmoothValueInt_020c21d8(int index)
{
    return g_sceneWork_020c50e0->smoothValues[index].current >> 12;
}
