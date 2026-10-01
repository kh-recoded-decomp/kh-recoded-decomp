#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    s8 inUse;
    u8 pad_01[0x137];
} EntrySlot;

typedef struct {
    EntrySlot *slots;
    s32 slotCount;
    s16 groupId;
    u8 pad_0a[0x02];
    BOOL fixedSlots;
    NNSFndLink link;
} EntryGroup;

typedef struct {
    BOOL initialized;
    NNSFndList groupList;
    s32 groupCount;
    u16 nextGroupId;
} EntryRegistry;

extern EntryRegistry g_entryRegistry_020b5608;
extern EntryGroup *func_ov021_020a8810(int groupId);
extern void UnpackExtendedData_020a8234(void *slot);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *memory);
extern void RemoveIntrusiveListObject_020129d8(NNSFndList *list, void *object);

void func_ov021_020a8a68(int groupId)
{
    EntryRegistry *registry = &g_entryRegistry_020b5608;
    EntryGroup *group = func_ov021_020a8810(groupId);
    int slotIndex;

    if (group != NULL) {
        for (slotIndex = 0; slotIndex < group->slotCount; slotIndex++) {
            UnpackExtendedData_020a8234(&group->slots[slotIndex]);
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(group->slots);
        RemoveIntrusiveListObject_020129d8(&registry->groupList, group);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(group);
        registry->groupCount--;
    }
}
