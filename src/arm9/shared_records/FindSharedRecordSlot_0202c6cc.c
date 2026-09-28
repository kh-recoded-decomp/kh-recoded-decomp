#include "nitro/types.h"

typedef struct SharedRecordSlot {
    u16 refCount;
    u8 pad_02[0x12];
    char name[0x20];
} SharedRecordSlot;

extern struct {
    u8 pad_00[8];
    SharedRecordSlot *table;
} data_02060564;

extern int strcmp(const char *a, const char *b);

SharedRecordSlot *FindSharedRecordSlot_0202c6cc(const char *key)
{
    int i;
    SharedRecordSlot *unused;
    u32 keyIsId;
    SharedRecordSlot *entry;
    SharedRecordSlot *table;
    u16 refCount;

    unused = 0;
    table = data_02060564.table;
    i = 0;
    keyIsId = (u32)key & 0x80000000;

    do {
        entry = &table[i];
        refCount = entry->refCount;
        if (refCount != 0) {
            u32 id = *(u32 *)entry->name;
            u32 entryIsId = id & 0x80000000;
            if (keyIsId != 0 && entryIsId != 0 && (u32)key == id) {
                return entry;
            }
            if (keyIsId == 0 && entryIsId == 0 && strcmp(entry->name, key) == 0) {
                return entry;
            }
        }
        i++;
        if (refCount == 0) {
            unused = entry;
        }
    } while (i < 0xb0);
    return unused;
}
