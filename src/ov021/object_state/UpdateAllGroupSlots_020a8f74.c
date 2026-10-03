#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    u8 data[0x138];
} GroupSlot;

typedef struct {
    GroupSlot *slots;
    s32 slotCount;
    s16 groupId;
} EntryGroup;

typedef struct {
    BOOL initialized;
    NNSFndList groups;
} GroupRegistry;

extern BOOL g_groupsInitialized_020b5608;
extern GroupRegistry g_groupRegistry_020b5608;
extern void *NNS_FndGetNextListObject_02012a38(NNSFndList *list, const void *object);
extern void func_ov021_020a8408(GroupSlot *slot);

void UpdateAllGroupSlots_020a8f74(void)
{
    int i;
    EntryGroup *group;
    EntryGroup *next;
    GroupRegistry *registry = &g_groupRegistry_020b5608;

    if (!g_groupsInitialized_020b5608) {
        return;
    }
    group = NNS_FndGetNextListObject_02012a38(&registry->groups, NULL);
    while (group != NULL) {
        next = NNS_FndGetNextListObject_02012a38(&registry->groups, group);
        for (i = 0; i < group->slotCount; i++) {
            func_ov021_020a8408(&group->slots[i]);
        }
        group = next;
    }
}

