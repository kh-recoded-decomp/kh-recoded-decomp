#include "nitro/types.h"

extern u32 gOv030SceneWork;

u32 GetOv030SceneReferenceAxis(void)
{
    if (gOv030SceneWork != 0) {
        return gOv030SceneWork + 0x24;
    }
    return 0;
}
