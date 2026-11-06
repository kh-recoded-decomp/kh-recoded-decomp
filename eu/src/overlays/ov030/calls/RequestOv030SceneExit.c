#include "nitro/types.h"

extern u32 gOv030SceneWork;

void RequestOv030SceneExit(u8 value)
{
    *(u8 *)(gOv030SceneWork + 8) = value;
    *(u16 *)(gOv030SceneWork + 6) = *(u16 *)(gOv030SceneWork + 6) | 0x4000;
}
