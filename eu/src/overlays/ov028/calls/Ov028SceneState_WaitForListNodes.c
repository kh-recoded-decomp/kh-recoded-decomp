#include "nitro/types.h"

extern u32 gOv028FieldSceneWorkStorage;
extern s32 AreAllListNodesReady(void);
extern void RequestFieldEntryResourceDelivery(s32 value);

u32 Ov028SceneState_WaitForListNodes(void)
{
    s32 value = AreAllListNodesReady();

    if (value != 0) {
        RequestFieldEntryResourceDelivery(value);
        *(u16 *)(gOv028FieldSceneWorkStorage + 6) = *(u16 *)(gOv028FieldSceneWorkStorage + 6) | 0x8000;
        return 3;
    }
    return 0xffffffff;
}
