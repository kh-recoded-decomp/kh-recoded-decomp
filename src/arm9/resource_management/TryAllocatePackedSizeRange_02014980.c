#include "nitro/types.h"

extern int data_0205a900;
extern int data_0205a904;
extern int func_02014458(int *usedListHead, int *freeListHead, int start, int size);

BOOL TryAllocatePackedSizeRange_02014980(u32 packedSize, void *param2, void *param3, u32 param4)
{
    int width = (packedSize & 0xffff) << 3;
    int height = ((packedSize & 0xffff0000) >> 16) << 3;

    return func_02014458(&data_0205a900, &data_0205a904, width, height) == 0;
}
