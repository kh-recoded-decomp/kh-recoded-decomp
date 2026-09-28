#include "nitro/types.h"

extern u32 g_ov038Context_020bd144;
extern void Slot_UnlinkAll_0204f104(void *p);
extern int Obj_Release_0204eff8(void *object);

void ReleaseOv038SlotPools_020bb0c0(void)
{
    u32 pool;
    s32 index;

    index = 0;
    pool = g_ov038Context_020bd144 + 0x40;
    do {
        Slot_UnlinkAll_0204f104((void *)(pool + index * 0x6434));
        Obj_Release_0204eff8((void *)(pool + index * 0x6434));
        index = index + 1;
    } while (index < 2);
}
