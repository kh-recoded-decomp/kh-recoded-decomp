#include "nitro/types.h"

extern void *DestroyTaskObjectWrapper();

extern u32 gScreenFadeTaskHandle;

void func_ov001_0206a714(void)
{
    DestroyTaskObjectWrapper(gScreenFadeTaskHandle);
    gScreenFadeTaskHandle = 0xffffffff;
}
