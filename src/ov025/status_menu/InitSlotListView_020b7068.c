#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RowEntry {
    u16 value;
    u16 y;
    u32 unk_4;
} RowEntry;

typedef struct RowTable {
    u8 pad_00[6];
    u16 count;
    RowEntry entries[1];
} RowTable;

typedef struct SlotRecord {
    u8 pad_00[6];
    u16 parent;
    u16 index;
} SlotRecord;

typedef struct SlotTable {
    u8 pad_00[6];
    u16 count;
    SlotRecord *records[1];
} SlotTable;

typedef struct ListData {
    u16 id;
    u8 pad_02[2];
    RowTable *table;
    SlotTable *slotTable;
} ListData;

typedef struct SavedSelection {
    int id;
    u16 slotIds[3];
} SavedSelection;

typedef struct ListOverlayCell {
    int cellIndex;
    int group;
    fx32 x;
    fx32 y;
} ListOverlayCell;

typedef char *(*PathResolver)(int resourceId);

typedef struct ListView {
    void (*onChange)(void);
    ListData *data;
    BOOL asyncLoad;
    u32 field;
    u16 palette[0x30];
    SlotRecord *slots[3];
    u8 mode;
    u8 *entryStates;
    u8 *recordFlags;
    void *cellSet;
    void *highlightCell;
    void *cursorCell;
    int scrollPos;
    int scrollTarget;
    BOOL scrolling;
    int busy;
    int cursorIndex;
    int selectedIndex;
    int overlayCellCount;
    ListOverlayCell overlayCells[8];
    int normalSequence;
    int highlightSequence;
    u16 prevTouch[4];
} ListView;

typedef struct ListViewConfig {
    PathResolver resolvePath;
    void (*onChange)(void);
    ListData *data;
    BOOL asyncLoad;
    u32 field;
    u8 mode;
    void *cellSet;
    void *highlightCell;
    void *cursorCell;
    int maxSlots;
    int normalSequence;
    int highlightSequence;
} ListViewConfig;

extern void func_01ff8830(void *dst, int value, u32 size);
extern void MIi_CpuClear16_01ff8684(u16 value, void *dest, u32 size);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int alignment);
extern SavedSelection *func_020505a8(void);
extern void SetParamWord8_02050620(int value);
extern void func_ov025_020b6ca0(ListView *list, int entryIndex);
extern void func_ov025_020b6d00(ListView *list, int entryIndex);
extern void LoadPanelResource_020b6c2c(ListView *panel, PathResolver resolvePath);

static inline int GetEntryScroll(RowEntry *entries, int index)
{
    entries += index;
    return -((entries->y - 2) * 8);
}

void InitSlotListView_020b7068(ListView *list, ListViewConfig *config)
{
    SavedSelection *selection;
    SlotTable *slotTable;
    RowTable *table;
    int count;
    int index;
    int scroll;
    ListData *data;

    func_01ff8830(list, 0, sizeof(ListView));
    data = config->data;
    list->data = data;
    list->asyncLoad = config->asyncLoad;
    list->onChange = config->onChange;
    list->field = config->field;
    list->cellSet = config->cellSet;
    list->highlightCell = config->highlightCell;
    list->cursorCell = config->cursorCell;
    list->mode = config->mode;
    list->scrolling = FALSE;
    list->busy = 0;
    list->entryStates = NNSi_FndAllocFromDefaultHeapEx_0202a19c(data->table->count, -4);
    list->recordFlags = NNSi_FndAllocFromDefaultHeapEx_0202a19c(list->data->slotTable->count, -4);
    func_01ff8830(list->entryStates, 0, list->data->table->count);
    func_01ff8830(list->recordFlags, 0, list->data->slotTable->count);
    MIi_CpuClear16_01ff8684(0x2d6b, list->palette, sizeof(list->palette));
    selection = func_020505a8();
    if (config->data->id != selection->id) {
        SetParamWord8_02050620(-1);
    }
    slotTable = list->data->slotTable;
    table = list->data->table;
    if (selection->id >= 0) {
        for (count = 0; count < 3; count++) {
            if (selection->slotIds[count] == 0xffff) {
                break;
            }
            list->slots[count] = slotTable->records[selection->slotIds[count]];
        }
        if (count > config->maxSlots) {
            count = config->maxSlots;
        }
        if (count > 0) {
            index = list->slots[count - 1]->index;
        } else {
            index = 0;
        }
    } else {
        index = 0;
    }
    list->normalSequence = config->normalSequence;
    list->highlightSequence = config->highlightSequence;
    list->cursorIndex = index;
    list->selectedIndex = index;
    scroll = GetEntryScroll(table->entries, index);
    if (scroll > 0) {
        scroll = 0;
    } else if (scroll < -256) {
        scroll = -256;
    }
    list->scrollPos = scroll;
    list->scrollTarget = scroll;
    func_ov025_020b6ca0(list, index);
    func_ov025_020b6d00(list, index);
    LoadPanelResource_020b6c2c(list, config->resolvePath);
}
