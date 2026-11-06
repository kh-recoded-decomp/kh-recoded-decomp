#include "nitro/types.h"

extern int gResumeModeTaskHandle;
extern void *DestroyTaskObjectWrapper(int argument0);

void DestroyResumeModeTask(void)
{
    DestroyTaskObjectWrapper(gResumeModeTaskHandle);
    gResumeModeTaskHandle = -1;
}
