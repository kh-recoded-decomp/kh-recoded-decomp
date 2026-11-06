#include "nitro/types.h"

extern u8 *gOv031SceneWorkStorage;

u32 GetSceneScrollTargetSpeed(void)
{
    return *(const u32 *)(gOv031SceneWorkStorage + 0x30);
}
