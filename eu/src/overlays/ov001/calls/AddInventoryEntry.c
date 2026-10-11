#pragma opt_propagation off

#include "src/overlays/ov001/InventoryEntry.h"
#include "src/overlays/ov001/SessionFlags.h"

extern void MI_CpuFill8(void *destination, u8 value, u32 size);
extern int func_02029254(int itemId, const InventoryRecordOptions *options);
extern void ShowChoiceDetails_02072254(const InventoryEntryDescriptor *entry, int result);
extern void AddSessionCounter(int counter, int amount);

int AddInventoryEntry(const InventoryEntryDescriptor *entry, int showDetails)
{
    InventoryRecordOptions options;
    int result;
    int id = GetInventoryEntryId(entry);

    if (id >= 0 && id <= 127) {
        MI_CpuFill8(&options, 0, sizeof(options));
        options.level = entry->level;
        options.kind = entry->kind;
        result = func_02029254(GetInventoryEntryId(entry), &options);
    } else {
        result = func_02029254(GetInventoryEntryId(entry), 0);
    }

    if (showDetails)
        ShowChoiceDetails_02072254(entry, result);
    SetSessionFlag(GetInventoryEntryId(entry));
    AddSessionCounter(10, 1);
    return result;
}
