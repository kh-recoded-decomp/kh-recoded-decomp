#include "nitro/types.h"

typedef struct SlotEntry {
    u8 data[0x2c];
} SlotEntry;

typedef struct SlotArrays {
    SlotEntry *entries;
    int count;
    s8 *ids;
} SlotArrays;

typedef struct SlotModelObject {
    u8 pad00[0x78];
    void *model;
    u8 pad7c[0x104 - 0x7c];
    SlotArrays slots;
    u32 param;
} SlotModelObject;

typedef struct SlotIdList {
    int pad00;
    int count;
    s8 *ids;
} SlotIdList;

typedef struct SlotModelDesc {
    int group;
    int variant;
    SlotIdList *idList;
    u8 pad0c[8];
    u32 param;
} SlotModelDesc;

extern u32 MakePaletteUploadParams40_020a968c(int group, int variant);
extern u32 MakePaletteUploadParams60_020a96b4(int group, int variant);
extern void *RetainOrInitializeSharedRecord_0202c80c(u32 fileId, int heap);
extern void *func_0202c48c(u32 fileId, u32 heapId);
extern void func_0202ed9c(void *object, void *record, void *block, int heap);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, int polygonId);
extern void func_0202f590(void *object, int value);
extern void func_0202f5b4(void *object, int color);
extern void AllocateObjectSlotArrays_020a90a4(SlotArrays *slots, int count, int heap);
extern char *GetTimedEntryKey_020a96dc(int id, int variant);
extern void AcquireSharedRecordState_020a9054(void *state, char *key, void *object, int heap);

void LoadSlotModelObject_020a9814(SlotModelObject *object, SlotModelDesc *desc, u8 bank)
{
    int heap;
    void *record;
    void *block;
    SlotIdList *idList;
    int i;
    int slot;
    int id;
    char *key;
    SlotArrays *slots;

    heap = bank + 8;
    object->param = desc->param;
    record = RetainOrInitializeSharedRecord_0202c80c(MakePaletteUploadParams40_020a968c(desc->group, desc->variant), heap);
    block = func_0202c48c(MakePaletteUploadParams60_020a96b4(desc->group, desc->variant), 0x11);
    func_0202ed9c(object, record, block, heap);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    Model_SetAllPolygonIds_0201a8c0(object->model, 0x3f);
    func_0202f590(object, 1);
    func_0202f5b4(object, 0x7fff);
    idList = desc->idList;
    i = 0;
    slots = &object->slots;
    slots->entries = NULL;
    slots->ids = NULL;
    slots->count = 0;
    AllocateObjectSlotArrays_020a90a4(slots, idList->count, heap);
    slot = 0;
    for (; i < idList->count; i++) {
        id = idList->ids[i];
        key = GetTimedEntryKey_020a96dc(id, desc->variant);
        if (key != NULL) {
            AcquireSharedRecordState_020a9054(&slots->entries[slot], key, object, heap);
            slots->ids[slot] = id;
            slot++;
        }
    }
}
