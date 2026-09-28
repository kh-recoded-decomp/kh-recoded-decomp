#include "nitro/types.h"

extern u8 *data_0205fe0c;

typedef struct RecordEntry
{
    u16 kind : 2;
    u16 unk_00_2 : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct SlotPair0Entry
{
    u8 pad_00[8];
    int weight;
    u8 pad_0C[0x3C];
} SlotPair0Entry;

extern RecordEntry *GetActiveRecordEntryOrNull_02029548(int index);
extern SlotPair0Entry *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void func_02051c80(void);
extern void func_02051cdc(void);
extern int func_020520b8(u8 first, u8 second);
extern s64 func_02023fc8(int dividend, int divisor);

BOOL ResolveMergedRecordEntry_020295c8(int index, RecordEntry *entry, u32 *outValue)
{
    int firstSlot;
    int secondSlot;
    u16 firstHandle;
    u16 secondHandle;
    RecordEntry *first;
    RecordEntry *second;
    SlotPair0Entry *firstInfo;
    SlotPair0Entry *secondInfo;
    SlotPair0Entry *mergedInfo;
    int mergedCategory;
    int divisor;
    int firstWeight;
    int secondWeight;
    int level;

    firstSlot = index * 2;
    secondSlot = firstSlot + 1;
    entry->active = 0;
    *outValue = 0xffffffff;

    firstHandle = *(u16 *)(data_0205fe0c + firstSlot * 2 + 0x2d84);
    if (firstHandle == 0xffff)
    {
        return FALSE;
    }
    if (firstHandle < 0x200)
    {
        *outValue = firstHandle;
        return TRUE;
    }
    secondHandle = *(u16 *)(data_0205fe0c + secondSlot * 2 + 0x2d84);
    if (secondHandle == 0xffff)
    {
        first = GetActiveRecordEntryOrNull_02029548((u16)(firstHandle - 0x200));
        *entry = *first;
        return TRUE;
    }

    first = GetActiveRecordEntryOrNull_02029548((u16)(firstHandle - 0x200));
    second = GetActiveRecordEntryOrNull_02029548((u16)(secondHandle - 0x200));
    firstInfo = GetRecordSlotPair0Entry_02051ec8((u8)first->category);
    secondInfo = GetRecordSlotPair0Entry_02051ec8((u8)second->category);

    entry->active = 1;
    entry->kind = first->kind | second->kind;
    entry->unk_00_2 = 0;

    func_02051c80();
    AcquireRecordSlot_02051d3c(0, 1);
    AcquireRecordSlot_02051d3c(5, 1);

    mergedCategory = func_020520b8(first->category, second->category);
    if (mergedCategory == -1)
    {
        mergedCategory = func_020520b8(second->category, first->category);
    }
    if (mergedCategory == -1)
    {
        entry->category = first->category;
        mergedInfo = firstInfo;
    }
    else
    {
        entry->category = (u8)mergedCategory;
        mergedInfo = GetRecordSlotPair0Entry_02051ec8(entry->category);
    }
    divisor = mergedInfo->weight;
    firstWeight = firstInfo->weight * (first->level + 1);
    secondWeight = secondInfo->weight * (second->level + 1);
    level = (int)func_02023fc8(firstWeight + secondWeight, divisor);
    entry->levelProgress = (u16)(func_02023fc8(firstWeight + secondWeight, divisor) >> 32);
    if (level > 100)
    {
        level = 100;
    }
    entry->level = (u16)level;

    ReleaseRecordSlot_02051dfc(5);
    ReleaseRecordSlot_02051dfc(0);
    func_02051cdc();
    return TRUE;
}
