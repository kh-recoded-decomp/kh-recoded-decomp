#include "nitro/types.h"

extern u8 *gCameraSceneGlobalStorage;

void SetCameraFollowLock(u32 value)
{
    *(u32 *)(gCameraSceneGlobalStorage + 0x48) = value;
}
