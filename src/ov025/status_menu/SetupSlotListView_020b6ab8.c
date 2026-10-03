#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenData {
    u8 pad_00[8];
    u32 size;
    u8 rawData[1];
} ScreenData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct BgGraphicsData {
    ScreenData *screen;
    CharacterData *character;
    void *palette;
} BgGraphicsData;

typedef struct ListEntry {
    u16 value;
    u16 column;
    u16 row;
    u16 unk_6;
} ListEntry;

typedef struct ListTable {
    u8 pad_00[6];
    u16 count;
    ListEntry entries[1];
} ListTable;

typedef struct SlotRecord {
    u8 pad_00[6];
    u16 entryIndex;
} SlotRecord;

typedef struct SlotTable {
    u8 pad_00[6];
    u16 count;
    SlotRecord *records[1];
} SlotTable;

typedef struct ListData {
    u8 pad_00[4];
    ListTable *table;
    SlotTable *slotTable;
} ListData;

typedef struct ScreenPos {
    fx32 x;
    fx32 y;
} ScreenPos;

typedef struct ListOverlayCell {
    int cellIndex;
    int group;
    fx32 x;
    fx32 y;
} ListOverlayCell;

typedef struct ListView {
    void (*onChange)(void);
    ListData *data;
    u8 pad_08[0x68];
    SlotRecord *slots[3];
    u8 pad_7c[4];
    u8 *entryStates;
    u8 pad_84[4];
    void *cellSet;
    u8 pad_8c[8];
    int baseX;
    u8 pad_98[0x14];
    int overlayCellCount;
    ListOverlayCell overlayCells[8];
    int normalSequence;
    int highlightSequence;
} ListView;

extern int *func_020505a8(void);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GXS_LoadBG2Char_02007b00(const void *src, u32 offset, u32 size);
extern void func_01ff869c(const void *src, void *dst, u32 size);
extern void func_ov025_020b65c4(ListView *list, int startSlot, SlotRecord **slots);
extern int func_0204f0b4(void *cellSet, int sequence, int arg);
extern void func_0204f13c(void *cellSet, int cellIndex, ScreenPos *pos);

void SetupSlotListView_020b6ab8(ListView *list, void *archive, void *screenBuffer)
{
    int *selection = func_020505a8();
    BgGraphicsData bg;
    ScreenPos pos;
    ListTable *table;
    SlotTable *slotTable;
    void *cellSet;
    ListOverlayCell *cell;
    ListEntry *entry;
    int i;
    int j;
    int sequence;

    GetBgDataFromArchive_0202b554(&bg, archive, 0, 0, -1);
    GXS_LoadBG2Char_02007b00(bg.character->rawData, 0, bg.character->size);
    func_01ff869c(bg.screen->rawData, screenBuffer, bg.screen->size);
    if (*selection >= 0) {
        func_ov025_020b65c4(list, 0, list->slots);
    } else {
        func_ov025_020b65c4(list, 0, NULL);
    }

    slotTable = list->data->slotTable;
    table = list->data->table;
    cellSet = list->cellSet;
    for (i = 0; i < table->count; i++) {
        entry = &table->entries[i];
        for (j = 0; j < slotTable->count; j++) {
            if (i == slotTable->records[j]->entryIndex) {
                break;
            }
        }
        if (j == slotTable->count) {
            sequence = (list->entryStates[i] == 0) ? list->normalSequence : list->highlightSequence;
            cell = &list->overlayCells[list->overlayCellCount];
            cell->cellIndex = func_0204f0b4(cellSet, sequence, 0);
            cell->group = entry->value;
            cell->x = entry->column << 15;
            cell->y = entry->row << 15;
            list->overlayCellCount++;
        }
    }
    for (i = 0; i < list->overlayCellCount; i++) {
        cell = &list->overlayCells[i];
        pos.x = cell->x + (list->baseX << 12);
        pos.y = cell->y;
        func_0204f13c(list->cellSet, cell->cellIndex, &pos);
    }
    if (list->onChange != NULL) {
        list->onChange();
    }
}
