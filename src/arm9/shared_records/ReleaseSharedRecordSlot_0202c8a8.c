#include "nitro/types.h"

typedef struct SharedRecordSlot {
    u16 refCount;
    u16 loaded;
    u16 pad_04;
    u16 pad_06;
    void *heap;
    void *data;
    void *extraBlock;
    u8 nameFlag;
} SharedRecordSlot;

extern void ReleaseResourceGroup_0202d338(void *group);
extern void ReleaseTexturePaletteResources_02019e60(void *pResData);
extern void NNSi_FndFreeToExpHeap_0202a240(void *block, void *heap);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

int ReleaseSharedRecordSlot_0202c8a8(SharedRecordSlot *slot)
{
    slot->refCount--;
    if (slot->refCount == 0) {
        if (slot->loaded != 0) {
            if (*(int *)slot->data == 0x4850414b) {
                ReleaseResourceGroup_0202d338(slot->data);
            } else {
                ReleaseTexturePaletteResources_02019e60(slot->data);
            }
            slot->loaded = 0;
            slot->pad_04 = 0;
        }
        slot->nameFlag = 0;
        NNSi_FndFreeToExpHeap_0202a240(slot->data, slot->heap);
        slot->data = 0;
        if (slot->extraBlock != 0) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(slot->extraBlock);
            slot->extraBlock = 0;
        }
        return 1;
    }
    return 0;
}
