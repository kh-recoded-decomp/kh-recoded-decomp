#include "nitro/types.h"

extern u8 *gOv030SceneWork;

u32 GetOv030FieldTransitionFlags(void)
{
    return *(const u16 *)(gOv030SceneWork + 0x6) & 0x60;
}
