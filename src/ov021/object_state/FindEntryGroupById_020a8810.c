#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    void *slots;
    s32 slotCount;
    s16 groupId;
} EntryGroup;

typedef struct {
    BOOL initialized;
    NNSFndList groups;
} GroupRegistry;

extern GroupRegistry g_groupRegistry_020b5608;
extern NNSFndList g_groupList_020b560c;
extern void *NNS_FndGetNextListObject_02012a38(NNSFndList *list, const void *object);

EntryGroup *FindEntryGroupById_020a8810(int groupId)
{
    GroupRegistry *registry = &g_groupRegistry_020b5608;
    EntryGroup *group = NNS_FndGetNextListObject_02012a38(&g_groupList_020b560c, NULL);
    while (group != NULL) {
        EntryGroup *next = NNS_FndGetNextListObject_02012a38(&registry->groups, group);
        if (group->groupId == groupId) {
            break;
        }
        group = next;
    }
    return group;
}
