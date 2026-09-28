#include "nitro/types.h"

typedef struct ResourceSlot {
    u8 pad_00[2];
    u16 refCount;
    u16 unk_04;
    u8 pad_06[0xc - 6];
    void *group;
    void *heapBlock;
} ResourceSlot;

extern void ReleaseResourceGroup_0202d338(void *group);
extern void ReleaseTexturePaletteResources_02019e60(void *pResData);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

/* Drops a slot's refcount; at zero, releases its resource. */
BOOL ReleaseResourceSlot_0202ca18(ResourceSlot *slot)
{
    slot->refCount = slot->refCount - 1;
    if (slot->refCount == 0) {
        if (*(u32 *)slot->group == 0x4850414b) {
            ReleaseResourceGroup_0202d338(slot->group);
        } else {
            ReleaseTexturePaletteResources_02019e60(slot->group);
        }
        slot->unk_04 = 0;
        if (slot->heapBlock != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(slot->heapBlock);
            slot->heapBlock = NULL;
        }
        return TRUE;
    }
    return FALSE;
}
