#include "nitro/types.h"

extern u8 *gOv031SceneWorkStorage;

u32 GetOv031FieldTransitionFlag(void)
{
    return *(const u16 *)(gOv031SceneWorkStorage + 0x6) & 0x20;
}
