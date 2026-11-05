#include "nitro/types.h"

extern int data_ov033_020baaa0;
extern void *DestroyTaskObjectWrapper(int argument0);

void DestroyResumeModeTask(void)
{
    DestroyTaskObjectWrapper(data_ov033_020baaa0);
    data_ov033_020baaa0 = -1;
}
