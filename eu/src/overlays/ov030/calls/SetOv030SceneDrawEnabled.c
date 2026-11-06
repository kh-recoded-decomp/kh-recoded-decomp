#include "nitro/types.h"

extern u32 gOv030SceneWork;

void SetOv030SceneDrawEnabled(BOOL enable)
{
    if (enable != 0) {
        *(u16 *)(gOv030SceneWork + 6) = *(u16 *)(gOv030SceneWork + 6) | 4;
        return;
    }
    *(u16 *)(gOv030SceneWork + 6) = *(u16 *)(gOv030SceneWork + 6) & 0xfffb;
}
