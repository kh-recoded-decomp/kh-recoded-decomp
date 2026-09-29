#include "nitro/types.h"

typedef struct StageEntry {
    u8 pad_00[0xa];
    u16 eventId;
    u16 groupId;
} StageEntry;

typedef struct StageManager {
    u8 pad_00000[0x18d88];
    void *linkedEntryList;
} StageManager;

extern StageManager *func_ov001_0209c3c0(void);
extern void *func_ov001_0208f27c(void *list);
extern StageEntry *func_ov001_0208f268(void *list, void *node);
extern void *func_ov001_0208f28c(void *node);
extern void *func_ov001_0209c040(s16 groupId);
extern u8 *GetStageEventRecord_0209c0ec(u32 id);
extern u16 func_ov001_0209c248(StageEntry *entry);
extern void func_ov001_0209c024(int listIndex, u16 entryId);

void ReleaseEventLinkedEntries_02097c10(u8 *eventRecord)
{
    StageManager *manager = func_ov001_0209c3c0();
    void *node = func_ov001_0208f27c(manager->linkedEntryList);

    while (node != NULL) {
        StageEntry *entry = func_ov001_0208f268(manager->linkedEntryList, node);
        u8 *record;

        node = func_ov001_0208f28c(node);
        if (entry->groupId != 0 && func_ov001_0209c040((s16)entry->groupId) != NULL && entry->eventId != 0) {
            record = GetStageEventRecord_0209c0ec(entry->eventId);
            if (record != NULL && record == eventRecord) {
                func_ov001_0209c024(4, func_ov001_0209c248(entry));
            }
        }
    }
}
