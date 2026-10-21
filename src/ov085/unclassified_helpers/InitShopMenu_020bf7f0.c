#pragma opt_dead_assignments off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct TextFrame {
    u16 values[8];
} TextFrame;

typedef struct SlotPoolConfig {
    u32 imageParams;
    u32 rest[3];
} SlotPoolConfig;

typedef struct WidgetPos {
    fx32 x;
    fx32 y;
} WidgetPos;

typedef struct Widget {
    u8 pad_00[0x14];
    int slot;
} Widget;

typedef struct Palette {
    u8 pad_00[0xc];
    u8 *data;
} Palette;

typedef struct SlotRow {
    s16 slots[6];
} SlotRow;

typedef struct ShopEntry {
    u8 pad_00[0xc];
} ShopEntry;

typedef struct ShopRecord {
    int entryIndex;
    u8 minLevel;
} ShopRecord;

typedef struct ShopItem {
    u8 *name;
    ShopEntry *entry;
    ShopRecord *record;
} ShopItem;

typedef struct ShopMenu {
    u8 pad_000;
    u8 state;
    u8 useCatalog;
    u8 tabChanged;
    u8 pad_004[8];
    int hasExtraTab;
    u8 pad_010[8];
    u32 savedBgMask;
    s16 listCount;
    u8 pad_01e[5];
    u8 visibleRows;
    u8 pad_024[0xcc];
    TextLayer titleText;
    TextLayer tabText;
    TextLayer infoText;
    TextLayer priceText;
    u8 pad_1c0[4];
    void *buyLabel;
    void *sellLabel;
    void *elements;
    void *cells;
    Widget *tabWidgets[10];
    Widget *tabCursor;
    Widget *tabHighlight;
    Widget *scrollTrack;
    Widget *scrollUp;
    Widget *scrollDown;
    Widget *scrollBar;
    SlotRow rows[7];
    u8 pad_268[0x10];
    u8 strings[0xc];
    ShopEntry entries[0x5c0];
    u8 pad_4784[0x8c];
    u8 detail[0x63c];
    ShopItem items[0x155];
    u8 pad_5e48[4];
    int itemCount;
    u8 pad_5e50[4];
    u8 palette[0x40];
    u8 *paletteSource;
    u8 bgData[8];
    Palette *bgPalette;
    void *bgFile;
} ShopMenu;

#define REG_DISPCNT (*(vu32 *)0x04000000)

extern u8 *data_0205fe0c;
extern const TextFrame data_ov085_020c22ec;
extern const SlotPoolConfig data_ov085_020c22dc;
extern const WidgetPos data_ov085_020c22d4;
extern char data_ov085_020c2384[];

extern void func_01ff8830(void *dest, int value, u32 size);
extern void func_01ff8710(const void *src, void *dest, u32 size);
extern BOOL func_ov039_020bc84c(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bit);
extern void func_ov039_020bc914(void);
extern void OpenTextFrame_020be5b8(u32 position, u32 size, int layer, void *text, TextFrame *frame);
extern void LoadPackedFileView_020ba25c(void *view, const char *path, BOOL fromTail);
extern void *func_ov027_020ba2a8(void *view, int index);
extern void *func_ov039_020bcb20(u8 *state);
extern BOOL SetTextColorIfFits_020bcd04(void *text, int limit, void *font);
extern void DrawTextAnchored_020015a0(void *text, int x, int y, int color, u32 flags, const void *str);
extern void *func_ov039_020bc18c(void);
extern void *func_ov039_020bc1bc(void);
extern u32 BuildSlotImageParams_020bc220(int slot, u32 low);
extern void InitObjManagerAndMark_020b9060(void *cells, SlotPoolConfig *config);
extern void PXI_Init_020b9078(void *cells, u32 imageParams);
extern void func_ov027_020b8f98(void *cells, u32 imageParams, int count);
extern void func_ov027_020b7e24(void *elements, u32 imageParams);
extern Widget *FindWidgetById_020b90a4(void *cells, int id);
extern void SetEntrySlotsVisible_020b9580(void *cells, Widget *widget, int visible);
extern WidgetPos *func_ov027_020b91a8(void *cells, Widget *widget);
extern void func_ov027_020b91c8(void *cells, Widget *widget, WidgetPos *pos, int mode);
extern void func_ov027_020b97b8(void *cells, Widget *widget, int mode);
extern int func_0204f0b4(void *cells, int kind, int flag);
extern void func_0204f13c(void *cells, int slot, WidgetPos *pos);
extern void func_0204f2e4(void *cells, int slot);
extern void func_0204f378(void *cells, int slot, int value);
extern void Slot_SetMode2Bit_0204f480(void *cells, int slot, int value);
extern void func_ov039_020bc318(int a, int b, int c, int d, int e, int f);
extern void func_ov036_020bc414(int a, int b, int c);
extern void func_ov034_020bde84(void *list, void *cells, int a, int b, int c, int d, int e, int f, int g);
extern void *func_0202c478(u32 fileId, int heap);
extern void GetBgDataFromArchive_0202b554(void *dst, void *file, int x, int y, int flags);
extern void func_02007250(void *dest, u32 offset, u32 size);
extern void func_ov085_020c1fb4(void *detail);
extern void AcquireRecordSlot_02051d3c(int slot, int value);
extern void RefreshEntryListIfUnlocked_020c1f78(void *list);
extern u16 SumRecordTableAEntries_020521f8(int count);
extern ShopRecord *func_02052224(int index);
extern u16 FilterItemsForTab_020c14c0(ShopMenu *menu, int kind);
extern void SetupStageParams_020bdf10(void *list, void *cells, int mode);

static inline void FillShopItem(ShopItem *item, u8 *name, ShopRecord *record, ShopMenu *menu)
{
    ShopEntry *entry;

    item->name = name;
    item->record = record;
    entry = &menu->entries[record->entryIndex];
    item->entry = entry;
}

BOOL InitShopMenu_020bf7f0(ShopMenu *menu)
{
    TextFrame frame;
    WidgetPos pos[6];
    SlotPoolConfig config;
    WidgetPos offset;
    s16 i;
    void *elements;
    void *cells;
    void *font;
    Widget *rowName;
    Widget *rowPrice;
    Widget *rowCount;
    Widget *rowIcon;
    Widget *rowOwned;
    Widget *rowMark;
    int labelId;
    int slot;
    int level;
    u8 *source;

    func_01ff8830(menu, 0, sizeof(ShopMenu));
    menu->useCatalog = func_ov039_020bc84c() != 0;
    menu->hasExtraTab = (!menu->useCatalog && IsGlobalPackedBitSet_02027304(0xbea)) ? 1 : 0;
    frame = data_ov085_020c22ec;
    func_ov039_020bc914();
    OpenTextFrame_020be5b8(0x8, 0x20018, 1, &menu->titleText, &frame);
    OpenTextFrame_020be5b8(0x30001, 0x2000a, 1, &menu->tabText, &frame);
    OpenTextFrame_020be5b8(0x50004, 0xe0018, 1, &menu->infoText, &frame);
    OpenTextFrame_020be5b8(0x150000, 0x30020, 1, &menu->priceText, &frame);
    LoadPackedFileView_020ba25c(menu->strings, data_ov085_020c2384, FALSE);
    menu->buyLabel = func_ov027_020ba2a8(menu->strings, 0xe);
    menu->sellLabel = func_ov027_020ba2a8(menu->strings, 0xf);
    font = func_ov039_020bcb20(data_0205fe0c);
    SetTextColorIfFits_020bcd04(&menu->titleText, 0xac, font);
    DrawTextAnchored_020015a0(&menu->titleText, 0xbe, 2, 2, 0x20, font);
    labelId = 2;
    if (!menu->useCatalog) {
        labelId = 0;
    }
    DrawTextAnchored_020015a0(&menu->tabText, 4, 3, 2, 8, func_ov027_020ba2a8(menu->strings, labelId));
    menu->state = 1;

    elements = func_ov039_020bc18c();
    cells = func_ov039_020bc1bc();
    config = data_ov085_020c22dc;
    config.imageParams = BuildSlotImageParams_020bc220(2, 3);
    InitObjManagerAndMark_020b9060(cells, &config);
    PXI_Init_020b9078(cells, BuildSlotImageParams_020bc220(3, 2));
    func_ov027_020b8f98(cells, BuildSlotImageParams_020bc220(2, 7), 0x30);
    func_ov027_020b7e24(elements, BuildSlotImageParams_020bc220(2, 4));

    if (menu->hasExtraTab != 0) {
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 1), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 2), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 3), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 7), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 8), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0xb), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0xc), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0xe), 0);
        menu->tabCursor = FindWidgetById_020b90a4(cells, 0x44);
        menu->tabHighlight = FindWidgetById_020b90a4(cells, 0x43);
        menu->tabWidgets[0] = FindWidgetById_020b90a4(cells, 0x3c);
        menu->tabWidgets[1] = FindWidgetById_020b90a4(cells, 0x3d);
        menu->tabWidgets[2] = FindWidgetById_020b90a4(cells, 0x3e);
        menu->tabWidgets[3] = FindWidgetById_020b90a4(cells, 0x3f);
        menu->tabWidgets[4] = FindWidgetById_020b90a4(cells, 0x40);
        menu->tabWidgets[5] = FindWidgetById_020b90a4(cells, 0x43);
        menu->tabWidgets[6] = FindWidgetById_020b90a4(cells, 0x44);
        menu->tabWidgets[7] = FindWidgetById_020b90a4(cells, 0x47);
        menu->tabWidgets[8] = FindWidgetById_020b90a4(cells, 0x48);
        menu->tabWidgets[9] = FindWidgetById_020b90a4(cells, 0x4a);
    } else {
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x3c), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x3d), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x3e), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x3f), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x40), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x43), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x44), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x47), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x48), 0);
        SetEntrySlotsVisible_020b9580(cells, FindWidgetById_020b90a4(cells, 0x4a), 0);
        menu->tabCursor = FindWidgetById_020b90a4(cells, 8);
        menu->tabHighlight = FindWidgetById_020b90a4(cells, 7);
        menu->tabWidgets[0] = FindWidgetById_020b90a4(cells, 0);
        menu->tabWidgets[1] = FindWidgetById_020b90a4(cells, 1);
        menu->tabWidgets[2] = FindWidgetById_020b90a4(cells, 2);
        menu->tabWidgets[3] = FindWidgetById_020b90a4(cells, 3);
        menu->tabWidgets[4] = FindWidgetById_020b90a4(cells, 7);
        menu->tabWidgets[5] = FindWidgetById_020b90a4(cells, 8);
        menu->tabWidgets[6] = FindWidgetById_020b90a4(cells, 0xb);
        menu->tabWidgets[7] = FindWidgetById_020b90a4(cells, 0xc);
        menu->tabWidgets[8] = FindWidgetById_020b90a4(cells, 0xe);
    }

    rowName = FindWidgetById_020b90a4(cells, 0xf);
    rowPrice = FindWidgetById_020b90a4(cells, 0x10);
    rowCount = FindWidgetById_020b90a4(cells, 0x13);
    rowIcon = FindWidgetById_020b90a4(cells, 0x12);
    rowOwned = FindWidgetById_020b90a4(cells, 0x32);
    rowMark = FindWidgetById_020b90a4(cells, 5);
    pos[0] = *func_ov027_020b91a8(cells, rowName);
    pos[1] = *func_ov027_020b91a8(cells, rowPrice);
    pos[2] = *func_ov027_020b91a8(cells, rowCount);
    pos[3] = *func_ov027_020b91a8(cells, rowIcon);
    pos[4] = *func_ov027_020b91a8(cells, rowOwned);
    pos[5] = *func_ov027_020b91a8(cells, rowMark);
    func_ov027_020b97b8(cells, rowName, 2);
    func_ov027_020b97b8(cells, rowPrice, 2);
    menu->rows[0].slots[0] = rowName->slot;
    menu->rows[0].slots[1] = rowPrice->slot;
    menu->rows[0].slots[2] = rowCount->slot;
    menu->rows[0].slots[4] = rowOwned->slot;
    menu->rows[0].slots[5] = rowMark->slot;

    for (i = 0; i < 7; i++) {
        if (i) {
            slot = (s16)func_0204f0b4(cells, 0xf, 0);
            pos[0].y += 0x10000;
            func_0204f13c(cells, slot, &pos[0]);
            Slot_SetMode2Bit_0204f480(cells, slot, 2);
            func_0204f378(cells, slot, 1);
            menu->rows[i].slots[0] = slot;
            slot = (s16)func_0204f0b4(cells, 0x10, 0);
            pos[1].y += 0x10000;
            func_0204f13c(cells, slot, &pos[1]);
            Slot_SetMode2Bit_0204f480(cells, slot, 2);
            func_0204f378(cells, slot, 1);
            menu->rows[i].slots[1] = slot;
            slot = (s16)func_0204f0b4(cells, 2, 1);
            pos[2].y += 0x10000;
            func_0204f13c(cells, slot, &pos[2]);
            func_0204f378(cells, slot, 0);
            menu->rows[i].slots[2] = slot;
            slot = (s16)func_0204f0b4(cells, 0x1a, 0);
            pos[4].y += 0x10000;
            func_0204f13c(cells, slot, &pos[4]);
            func_0204f378(cells, slot, 0);
            menu->rows[i].slots[4] = slot;
            slot = (s16)func_0204f0b4(cells, 3, 1);
            pos[5].y += 0x10000;
            func_0204f13c(cells, slot, &pos[5]);
            func_0204f378(cells, slot, 0);
            menu->rows[i].slots[5] = slot;
        }
        slot = (s16)func_0204f0b4(cells, 1, 1);
        func_0204f13c(cells, slot, &pos[3]);
        func_0204f2e4(cells, slot);
        func_0204f378(cells, slot, 0);
        menu->rows[i].slots[3] = slot;
        pos[3].y += 0x10000;
    }

    func_ov027_020b97b8(cells, FindWidgetById_020b90a4(cells, 0xd), 2);
    SetEntrySlotsVisible_020b9580(cells, menu->tabHighlight, 0);
    menu->scrollTrack = FindWidgetById_020b90a4(cells, 0x11);
    menu->scrollUp = FindWidgetById_020b90a4(cells, 0x14);
    menu->scrollDown = FindWidgetById_020b90a4(cells, 0x15);
    menu->scrollBar = FindWidgetById_020b90a4(cells, 0x33);
    SetEntrySlotsVisible_020b9580(cells, menu->scrollUp, 0);
    SetEntrySlotsVisible_020b9580(cells, menu->scrollDown, 0);
    func_ov027_020b97b8(cells, menu->scrollUp, 2);
    func_ov027_020b97b8(cells, menu->scrollDown, 2);
    func_ov039_020bc318(2, 1, 1, 0, 3, 0);
    func_ov036_020bc414(3, 0, 0x60);
    menu->visibleRows = 7;
    menu->listCount = 1;
    func_ov034_020bde84(&menu->listCount, cells, 9, 0x1e, 0xc, 1, 0x10, 0, 0);
    offset = data_ov085_020c22d4;
    func_ov027_020b91c8(cells, FindWidgetById_020b90a4(cells, 0x16), &offset, 4);
    menu->elements = elements;
    menu->cells = cells;
    if (menu->useCatalog) {
        menu->bgFile = func_0202c478(BuildSlotImageParams_020bc220(2, 1), 0xe);
        GetBgDataFromArchive_0202b554(menu->bgData, menu->bgFile, -1, -1, 0);
        func_02007250(menu->bgPalette->data + 0x40, 0, 0x40);
    }
    func_ov085_020c1fb4(menu->detail);
    level = 0;
    AcquireRecordSlot_02051d3c(0, 0);
    AcquireRecordSlot_02051d3c(8, 0);
    menu->state = 2;
    RefreshEntryListIfUnlocked_020c1f78(menu->entries);
    if (!menu->useCatalog) {
        ShopItem *item = menu->items;
        int index;
        u8 *name = data_0205fe0c + 0x2ad8;
        int count;

        if (IsGlobalPackedBitSet_02027304(0xbea)) {
            level = 9;
        } else {
            for (; level < 8; level++) {
                if (!IsGlobalPackedBitSet_02027304(level + 0xa0b)) {
                    break;
                }
            }
        }
        count = SumRecordTableAEntries_020521f8(9);
        menu->itemCount = index = 0;
        for (; index < count; index++, name++) {
            ShopRecord *record = func_02052224(index);

            if (record->minLevel <= level) {
                FillShopItem(item, name, record, menu);
                item++;
                menu->itemCount++;
            }
        }
    }
    menu->listCount = FilterItemsForTab_020c14c0(menu, -1);
    menu->tabChanged = 0;
    SetupStageParams_020bdf10(&menu->listCount, menu->cells, 1);
    menu->savedBgMask = (REG_DISPCNT & 0x1f00) >> 8;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
    if (menu->useCatalog) {
        source = data_0205fe0c + 0x2bd8;
    } else {
        source = data_0205fe0c + 0x2c18;
    }
    menu->paletteSource = source;
    func_01ff8710(source, menu->palette, 0x40);
    return TRUE;
}
