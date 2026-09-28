#include "nitro/types.h"

extern u32 data_ov001_020a04d8;
extern void func_ov001_0207f648(void *node);

void DestroyListNodes_0207eef4(void)
{
    u8 *node;

    for (node = *(u8 **)(data_ov001_020a04d8 + 8); node != 0; node = *(u8 **)(node + 4)) {
        func_ov001_0207f648(node);
    }
    *(u32 *)(data_ov001_020a04d8 + 8) = 0;
}
