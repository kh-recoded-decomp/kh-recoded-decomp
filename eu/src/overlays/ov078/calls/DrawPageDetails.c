#include "src/overlays/ov078/PageMenu.h"

typedef struct RecordSlotPair0Entry {
    u8 reserved00[0x40];
    const char *name;
    u8 reserved44[4];
} RecordSlotPair0Entry;

/* Each layout has nine words; word seven is its text color. */
extern u32 data_ov078_020c5024[];
extern u32 gPageEmptyText[];
extern u16 gPageNameRankFormat[];
extern u16 gPageLevelFormat[];
extern u16 gRankGlyphCodepoints[];
extern u8 *GetPageTableEntry(u32 index);
extern BOOL IsGlobalPackedBitSet(int bit);
extern u32 ReadGlobalPackedBits(u32 bit, u32 width);
extern void *func_ov027_020ba2c8(int *view, int index);
extern int GetGridTableValue(int row, int column);
extern RecordSlotPair0Entry *GetRecordSlotPair0Entry(s32 index);
extern void *OS_SNPrintf_0202e094(char *dst, u32 length, const char *format, ...);
extern void DrawLayoutLine(PageMenu *menu, int line, const void *text, const void *suffix);

void DrawPageDetails(PageMenu *menu)
{
    u32 cursor = menu->cursor;
    PageTableEntry *entry = (PageTableEntry *)GetPageTableEntry(cursor);
    int extra = IsGlobalPackedBitSet(cursor + 0xa01);
    int count;
    int limit;
    int i;
    u16 suffix[4];
    u16 text[50];
    PageSlot *slot;
    RecordSlotPair0Entry *record;

    count = ReadGlobalPackedBits(cursor * 2 + 0x9f7, 2);
    count = (u32)(extra != 0) + count;
    limit = ReadGlobalPackedBits(0xf38, 4);
    if (limit > 5) {
        limit = 5;
    }
    if ((s32)cursor >= limit) {
        data_ov078_020c5024[1 * 9 + 7] = 4;
        DrawLayoutLine(menu, 1, func_ov027_020ba2c8(menu->messageView, 2), NULL);
        data_ov078_020c5024[1 * 9 + 7] = 2;
    } else {
        DrawLayoutLine(menu, 1, (void *)GetGridTableValue(cursor, -1), NULL);
    }
    extra = IsGlobalPackedBitSet(cursor + 0xa01);
    int unlocked = ReadGlobalPackedBits(cursor * 2 + 0x9f7, 2);
    if ((u32)(extra != 0) + unlocked == 0) {
        goto locked;
    }
    limit = ReadGlobalPackedBits(0xf38, 4);
    if (limit > 5) {
        limit = 5;
    }
    if ((s32)cursor >= limit) {
locked:
        data_ov078_020c5024[2 * 9 + 7] = 4;
        DrawLayoutLine(menu, 2, func_ov027_020ba2c8(menu->messageView, 2), NULL);
        data_ov078_020c5024[2 * 9 + 7] = 2;
        DrawLayoutLine(menu, 3, gPageEmptyText, NULL);
        DrawLayoutLine(menu, 4, gPageEmptyText, NULL);
        return;
    }
    for (i = 0; i < count; ++i) {
        slot = &entry->details[i];
        record = GetRecordSlotPair0Entry(slot->recordId);
        OS_SNPrintf_0202e094((char *)text, 50, (const char *)gPageNameRankFormat,
                           record->name, gRankGlyphCodepoints[slot->rank]);
        text[49] = 0;
        if (slot->level != 0) {
            OS_SNPrintf_0202e094((char *)suffix, 4, (const char *)gPageLevelFormat, slot->level);
            suffix[3] = 0;
        } else {
            suffix[0] = 0;
        }
        DrawLayoutLine(menu, i + 2, text, suffix);
    }
    for (; count < 3; ++count) {
        DrawLayoutLine(menu, count + 2, gPageEmptyText, NULL);
    }
}
