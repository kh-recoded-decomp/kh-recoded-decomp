#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    u8 active;
    s8 owner;
    u16 pad_02;
    u16 flags;
    u8 pad_06[0x10e];
    u32 soundHandle;
    u8 pad_118[0x20];
} SoundEntry;

typedef struct {
    SoundEntry *slots;
    s32 slotCount;
} EntryGroup;

typedef struct {
    BOOL initialized;
    NNSFndList groups;
} GroupRegistry;

extern BOOL g_groupsReady_020b5608;
extern GroupRegistry g_groupRegistry_020b5608;
extern void *NNS_FndGetNextListObject_02012a38(NNSFndList *list, const void *object);
extern void StopSoundSeqHandle_0204dbe4(u32 handle);

void StopEntrySoundsByOwner_020a8b9c(int owner)
{
    EntryGroup *group;
    EntryGroup *next;
    int i;
    SoundEntry *entry;
    GroupRegistry *registry = &g_groupRegistry_020b5608;

    if (g_groupsReady_020b5608 == 0) {
        return;
    }
    group = NNS_FndGetNextListObject_02012a38(&registry->groups, NULL);
    while (group != NULL) {
        next = NNS_FndGetNextListObject_02012a38(&registry->groups, group);
        for (i = 0; i < group->slotCount; i++) {
            entry = &group->slots[i];
            if (entry->owner == owner) {
                if (entry->soundHandle != 0) {
                    if (!(entry->flags & 0x80)) {
                        StopSoundSeqHandle_0204dbe4(entry->soundHandle);
                    }
                    entry->soundHandle = 0;
                }
                entry->active = 0;
            }
        }
        group = next;
    }
}
