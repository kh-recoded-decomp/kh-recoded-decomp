#include "nitro/types.h"

typedef struct RecordGroupEntry {
    u8 id;
    u8 reserved01[7];
} RecordGroupEntry;

typedef struct RecordGroup {
    u8 reserved00;
    u8 entryCount;
    u8 reserved02[0x1e];
    RecordGroupEntry *entries;
} RecordGroup;

typedef struct RecordGroupTable {
    u8 groupCount;
    u8 reserved01[7];
    RecordGroup *groups[];
} RecordGroupTable;

/* The owning context is larger; these are only its selection fields. */
typedef struct RecordGroupSelection {
    RecordGroupTable *table;
    u8 reserved04[9];
    s8 selectedGroup;
} RecordGroupSelection;

typedef char RecordGroupEntrySizeCheck[sizeof(RecordGroupEntry) == 8 ? 1 : -1];
typedef char RecordGroupSizeCheck[sizeof(RecordGroup) == 0x24 ? 1 : -1];
typedef char RecordGroupEntriesOffsetCheck[
    (u32)&((RecordGroup *)0)->entries == 0x20 ? 1 : -1];
typedef char RecordGroupTableGroupsOffsetCheck[
    (u32)&((RecordGroupTable *)0)->groups == 8 ? 1 : -1];
typedef char RecordGroupSelectionOffsetCheck[
    (u32)&((RecordGroupSelection *)0)->selectedGroup == 0xd ? 1 : -1];

extern RecordGroupSelection *data_ov001_020a048c;

BOOL FindRecordGroupByEntryId(int itemId, int *outGroup)
{
    RecordGroupSelection *scene = data_ov001_020a048c;

    /* Preserve the original four preferred-group probes before the full scan. */
    for (int attempt = 0; attempt < 4; attempt++) {
        int selected = scene->selectedGroup;
        if (selected >= 0) {
            RecordGroup *group = scene->table->groups[selected];
            u8 count = group->entryCount;
            for (int item = 0; item < count; item++) {
                int entryId = group->entries[item].id;
                if (entryId == itemId) {
                    *outGroup = selected;
                    return TRUE;
                }
            }
        }
    }

    RecordGroupTable *table;
    RecordGroup *group;
    RecordGroupEntry *entries;
    int groupCount;
    int count;
    int index;
    int item;
    int entryId;

    table = scene->table;
    groupCount = table->groupCount;
    index = 0;
    for (; index < groupCount; index++) {
        group = table->groups[index];
        count = group->entryCount;
        item = 0;
        if (count > 0) {
            entries = group->entries;
            do {
                entryId = entries[item].id;
                if (entryId == itemId) {
                    *outGroup = index;
                    return TRUE;
                }
                item++;
            } while (item < count);
        }
    }
    return FALSE;
}
