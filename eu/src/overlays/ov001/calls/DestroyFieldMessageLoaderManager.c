#include "nitro/types.h"

extern void ReleaseChannelManagerResources(int obj);
extern void NNSi_FndFreeFromDefaultHeap(u32 obj);

extern u32 data_ov001_020a04b8;

void DestroyFieldMessageLoaderManager(void)
{
    if (data_ov001_020a04b8 != 0) {
        ReleaseChannelManagerResources(data_ov001_020a04b8);
        NNSi_FndFreeFromDefaultHeap(data_ov001_020a04b8);
        data_ov001_020a04b8 = 0;
    }
}
