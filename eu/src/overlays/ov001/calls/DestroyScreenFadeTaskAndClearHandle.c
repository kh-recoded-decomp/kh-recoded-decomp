#include "nitro/types.h"

extern void *DestroyTaskObjectWrapper();

extern u32 gScreenFadeTaskHandle;

void DestroyScreenFadeTaskAndClearHandle(void)
{
    DestroyTaskObjectWrapper(gScreenFadeTaskHandle);
    gScreenFadeTaskHandle = 0xffffffff;
}
