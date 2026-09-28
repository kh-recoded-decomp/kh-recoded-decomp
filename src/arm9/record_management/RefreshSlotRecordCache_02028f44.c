#include "nitro/types.h"

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
    u8 pad_0C[0x18];
    int unk_24;
    u8 pad_28[0x20];
} SlotPair0Entry;

typedef struct CachedSlot
{
    int state;
    int value;
    RecordEntry entry;
} CachedSlot;

typedef struct RecordCounters
{
    u16 categoryCounts[0x80];
    u16 totalCount;
    u16 freeCount;
    CachedSlot slots[16];
} RecordCounters;

extern u8 *data_0205fe0c;
extern RecordCounters data_0205fec4;
extern RecordEntry *GetActiveRecordEntryOrNull_02029548(int index);
extern BOOL ResolveRecordHandle_02029574(int index, RecordEntry *entry, u32 *outValue);
extern SlotPair0Entry *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void OpenRecordManager_02051c80(void);
extern void CloseRecordManager_02051cdc(void);

void RefreshSlotRecordCache_02028f44(void)
{
    int i;
    RecordCounters *counters = &data_0205fec4;
    CachedSlot *slot;
    u32 handle;

    OpenRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(0, 1);
    AcquireRecordSlot_02051d3c(5, 1);
    for (i = 0; i < 16; i++)
    {
        slot = &counters->slots[i];
        if (ResolveRecordHandle_02029574(i, &slot->entry, &handle) && handle == 0xffffffff)
        {
            RecordEntry *source = GetActiveRecordEntryOrNull_02029548((u16)(*(u16 *)(data_0205fe0c + i * 2 + 0x2d84) - 0x200));
            if (source->unk_00_2 == 0)
            {
                slot->value = GetRecordSlotPair0Entry_02051ec8((u8)slot->entry.category)->weight;
            }
            else
            {
                slot->value = 0;
            }
            slot->state = !slot->entry.active ? 1 : 2;
        }
        else if (handle != 0xffffffff)
        {
            slot->value = GetRecordSlotPair0Entry_02051ec8(handle)->unk_24;
            slot->state = 3;
        }
        else
        {
            slot->value = 0;
            slot->state = 0;
        }
    }
    ReleaseRecordSlot_02051dfc(5);
    ReleaseRecordSlot_02051dfc(0);
    CloseRecordManager_02051cdc();
}
