#include "nitro/types.h"

extern u8 *gOv030SceneWork;

u8 GetOv030SceneLock(void)
{
    return *(const u8 *)(gOv030SceneWork + 0x9);
}
