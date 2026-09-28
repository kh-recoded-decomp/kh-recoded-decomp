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

extern s32 ContainsMatchingEntry_02034900(Record *self, u32 kind);
extern s32 func_02034bc8(Record *rec);
extern u8 *func_0203625c(u8 id);
extern BOOL func_ov001_020681e8(u8 *entry, u32 kind);
extern int func_ov001_02067ed4(void);
extern int func_ov001_02068344(int group, s8 slot);
extern Registry *func_02036230(void);
extern int GetSignedByteAt2_02067f94(u8 *entry);

BOOL func_ov001_020845dc(Record *record, Unit *unit)
{
    if (record->kind != 4 && unit->slotIndex < 0 && ContainsMatchingEntry_02034900(record, 1))
    {
        u8 *ids = (u8 *)func_02034bc8(record);
        int i;
        int expected;
        u8 id;
        EntryTable *table;
        u8 *entry;

        for (i = 0; i < 4; i++)
        {
            if (func_ov001_020681e8(func_0203625c(ids[i]), 1))
                break;
        }
        expected = func_ov001_02068344(func_ov001_02067ed4(), -1 - unit->slotIndex);
        id = ids[i];
        table = *func_02036230()->tables;
        entry = (id == 0xFF) ? NULL : table->entries + id * 0x14;
        if (expected == GetSignedByteAt2_02067f94(entry))
            return FALSE;
    }
    return TRUE;
}
