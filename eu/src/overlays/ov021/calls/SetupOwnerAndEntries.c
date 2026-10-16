#include "nitro/types.h"

typedef struct EntryDesc EntryDesc;

typedef struct Entry {
    u8 unknown00[0x154];
} Entry;

typedef struct Owner {
    void *context;
    u8 unknown04[4];
    Entry *entries;
    u8 unknown0c[0x15 - 0xc];
    u8 count;
} Owner;

extern void InitEntryPool(Owner *owner, EntryDesc *descs, int descCount, int slotCount);
extern void InitPoolEntry(Entry *entry, void *context, int first, int second, int index);

void SetupOwnerAndEntries(void *storage, int first, int second, EntryDesc *descs,
                          int descCount, int slotCount)
{
    Owner *owner = storage;
    int i;

    InitEntryPool(owner, descs, descCount, slotCount);
    for (i = 0; i < owner->count; i++) {
        InitPoolEntry(&owner->entries[i], owner->context, first, second, i);
    }
}
