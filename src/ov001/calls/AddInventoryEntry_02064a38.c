#pragma opt_propagation off
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


static inline int GetInventoryEntryId(const InventoryEntryDescriptor *entry)
{
    return (u16)entry->itemId;
}

int AddInventoryEntry_02064a38(const InventoryEntryDescriptor *entry, int showDetails);

#endif

#ifndef RECODED_SESSION_FLAGS_H
#define RECODED_SESSION_FLAGS_H

#include "nitro/types.h"

void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
void SetSessionFlag_020645dc(int bitOffset);

#endif


extern void MI_CpuFill8_01ff8830(void *destination, u8 value, u32 size);
extern int func_02029240(int itemId, const InventoryRecordOptions *options);
extern void ShowChoiceDetails_02072254(const InventoryEntryDescriptor *entry, int result);
extern void AddSessionCounter_02063a80(int counter, int amount);

int AddInventoryEntry_02064a38(const InventoryEntryDescriptor *entry, int showDetails)
{
    InventoryRecordOptions options;
    int result;
    int id = GetInventoryEntryId(entry);

    if (id >= 0 && id <= 127) {
        MI_CpuFill8_01ff8830(&options, 0, sizeof(options));
        options.level = entry->level;
        options.kind = entry->kind;
        result = func_02029240(GetInventoryEntryId(entry), &options);
    } else {
        result = func_02029240(GetInventoryEntryId(entry), 0);
    }

    if (showDetails)
        ShowChoiceDetails_02072254(entry, result);
    SetSessionFlag_020645dc(GetInventoryEntryId(entry));
    AddSessionCounter_02063a80(10, 1);
    return result;
}
