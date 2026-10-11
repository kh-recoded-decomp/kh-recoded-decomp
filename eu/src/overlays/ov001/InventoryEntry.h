#ifndef RECODED_INVENTORY_ENTRY_H
#define RECODED_INVENTORY_ENTRY_H

#include "nitro/types.h"

typedef struct InventoryEntryDescriptor {
    s16 itemId;
    u8 level;
    u8 kind;
} InventoryEntryDescriptor;

typedef struct InventoryRecordOptions {
    u16 kind : 2;
    u16 reserved0 : 14;
    u16 reserved1 : 1;
    u16 level : 7;
    u16 reserved2 : 8;
} InventoryRecordOptions;

/* The compact ID is passed to the inventory factory as an unsigned 16-bit value. */
static inline int GetInventoryEntryId(const InventoryEntryDescriptor *entry)
{
    return (u16)entry->itemId;
}

int AddInventoryEntry(const InventoryEntryDescriptor *entry, int showDetails);

#endif
