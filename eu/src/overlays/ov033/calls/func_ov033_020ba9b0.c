#include "nitro/types.h"

extern int data_ov033_020baaa0;
extern void *DestroyTaskObjectWrapper(int argument0);

void func_ov033_020ba9b0(void)
{
    DestroyTaskObjectWrapper(data_ov033_020baaa0);
    data_ov033_020baaa0 = -1;
}
