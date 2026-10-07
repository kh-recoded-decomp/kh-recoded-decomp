#include "nitro/types.h"

typedef struct Record
{
    s32 base;
    s32 kind;
} Record;

typedef struct Unit
{
    u8 pad_00[0x80];
    s8 slotIndex;
} Unit;

typedef struct EntryTable
{
    u8 pad_00[0xAC];
    u8 *entries;
} EntryTable;

typedef struct Registry
{
    u8 pad_00[0x4];
    EntryTable **tables;
} Registry;

extern s32 ContainsMatchingEntry(Record *self, u32 kind);
extern s32 Record_GetKindPayloadAddress(Record *rec);
extern u8 *GetWorldMeshNamedEntry(u8 id);
extern BOOL func_ov001_020681e8(u8 *entry, u32 kind);
extern int func_ov001_02067ed4(void);
extern int func_ov001_02068344(int group, s8 slot);
extern Registry *GetActorRegistry(void);
extern int GetSignedByteAt2(u8 *entry);

BOOL func_ov001_02084604(Record *record, Unit *unit)
{
    if (record->kind != 4 && unit->slotIndex < 0 && ContainsMatchingEntry(record, 1))
    {
        u8 *ids = (u8 *)Record_GetKindPayloadAddress(record);
        int i;
        int expected;
        u8 id;
        EntryTable *table;
        u8 *entry;

        for (i = 0; i < 4; i++)
        {
            if (func_ov001_020681e8(GetWorldMeshNamedEntry(ids[i]), 1))
                break;
        }
        expected = func_ov001_02068344(func_ov001_02067ed4(), -1 - unit->slotIndex);
        id = ids[i];
        table = *GetActorRegistry()->tables;
        entry = (id == 0xFF) ? NULL : table->entries + id * 0x14;
        if (expected == GetSignedByteAt2(entry))
            return FALSE;
    }
    return TRUE;
}
