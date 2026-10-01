#include "nitro/types.h"

typedef struct HeapBlock HeapBlock;

typedef struct FieldObject {
    u8 pad_00[0x6c];
    u8 resource[0x170 - 0x6c];
    s16 soundHandle;
    u8 pad_172[0x1c4 - 0x172];
    void *buffers[4];
    HeapBlock **valueSlots;
    u8 pad_1d8[0x1ea - 0x1d8];
    u16 valueSlotCount;
} FieldObject;

extern void func_0202eee8(void *resource);
extern void func_ov021_020a8a68(int handle);
extern void FreeBlockChain_020a2e84(HeapBlock **head);
extern void ReleaseIfSet_020a2e70(void **ptr);

void ReleaseFieldObjectResources_020a2ea0(FieldObject *object)
{
    int index;

    func_0202eee8(object->resource);
    func_ov021_020a8a68(object->soundHandle);
    for (index = 0; index < object->valueSlotCount; index++) {
        FreeBlockChain_020a2e84(&object->valueSlots[index]);
    }
    ReleaseIfSet_020a2e70(&object->buffers[0]);
    ReleaseIfSet_020a2e70(&object->buffers[1]);
    ReleaseIfSet_020a2e70(&object->buffers[2]);
    ReleaseIfSet_020a2e70(&object->buffers[3]);
    ReleaseIfSet_020a2e70((void **)&object->valueSlots);
}
