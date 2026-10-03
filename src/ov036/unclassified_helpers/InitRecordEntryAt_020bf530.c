#include "nitro/types.h"

typedef struct RecordPoint {
    s32 x;
    s32 y;
} RecordPoint;

typedef struct RecordEntry {
    s32 recordIndex;
    RecordPoint position;
    u32 flags;
} RecordEntry;

extern u8 *data_ov036_020c3844;
extern int func_0204f0b4(void *list, void *resource, int arg);
extern void func_0204f204(void *list, int index, int value);
extern void func_0204f480(void *list, int index, int value);
extern void func_0204f378(void *list, int index, int value);
extern void func_0204f2c0(void *list, int index);
extern void func_0204f13c(void *list, int index, RecordPoint *position);

void InitRecordEntryAt_020bf530(RecordEntry *entry, void *resource, RecordPoint *position, RecordPoint *offset)
{
    int index = func_0204f0b4(data_ov036_020c3844 + 0x18, resource, 0);

    func_0204f204(data_ov036_020c3844 + 0x18, index, 0);
    func_0204f480(data_ov036_020c3844 + 0x18, index, 0);
    func_0204f378(data_ov036_020c3844 + 0x18, index, 0);
    func_0204f2c0(data_ov036_020c3844 + 0x18, index);
    entry->flags = 0;
    entry->recordIndex = index;
    entry->position.x = position->x;
    entry->position.y = position->y;
    if (offset != NULL) {
        entry->position.x += offset->x;
        entry->position.y += offset->y;
    }
    func_0204f13c(data_ov036_020c3844 + 0x18, index, &entry->position);
}
