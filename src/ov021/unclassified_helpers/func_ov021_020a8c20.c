#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    s8 inUse;
    s8 actorId;
    s8 anchorMode;
    u8 pad_03;
    u16 flags;
    u8 pad_06[0x132];
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

extern BOOL g_registryInitialized_020b5608;
extern EntryRegistry g_entryRegistry_020b5608;
extern void *NNS_FndGetNextListObject_02012a38(NNSFndList *list, void *object);

BOOL func_ov021_020a8c20(int actorId)
{
    BOOL finished = TRUE;
    EntryRegistry *registry = &g_entryRegistry_020b5608;
    EntryGroup *group;
    EntryGroup *nextGroup;
    int slotIndex;

    if (g_registryInitialized_020b5608 == FALSE) {
        return finished;
    }
    group = NNS_FndGetNextListObject_02012a38(&registry->groupList, NULL);
    while (group != NULL && finished) {
        nextGroup = NNS_FndGetNextListObject_02012a38(&registry->groupList, group);
        for (slotIndex = 0; slotIndex < group->slotCount; slotIndex++) {
            EntrySlot *slot = &group->slots[slotIndex];
            if (slot->actorId == actorId && slot->inUse != 0) {
                if (!(slot->flags & 4)) {
                    finished = FALSE;
                }
                break;
            }
        }
        group = nextGroup;
    }
    return finished;
}
