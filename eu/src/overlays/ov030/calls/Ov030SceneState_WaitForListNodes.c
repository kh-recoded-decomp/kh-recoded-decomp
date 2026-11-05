#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern s32 AreAllListNodesReady(void);
extern void RequestFieldEntryResourceDelivery(void);

u32 Ov030SceneState_WaitForListNodes(void)
{
    s32 ready;

    ready = AreAllListNodesReady();
    if (ready == 0) {
        return 0xffffffff;
    }
    RequestFieldEntryResourceDelivery();
    *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) | 0x8000;
    return 3;
}
