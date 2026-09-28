#include "nitro/types.h"

extern int data_02060394;
extern void *NNSi_FndAllocFromExpHeapEx_0202a1e4(u32 size, void **heap);
extern void *func_0202a4b0(void *object, void *descriptor, void *userData, int useTailAlloc);

void *Obj_CreateWithTailWork_0202a47c(void *descriptor, void *userData)
{
    return func_0202a4b0(NNSi_FndAllocFromExpHeapEx_0202a1e4(0x2c, *(void **)&data_02060394), descriptor, userData, 1);
}
