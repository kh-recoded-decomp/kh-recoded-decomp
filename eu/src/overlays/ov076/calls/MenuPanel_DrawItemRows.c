#include "src/overlays/MenuImageQuad.h"

typedef union RecordHeader {
    u16 raw;
    struct {
        u16 kind : 2;
        u16 rank : 3;
        u16 progress : 11;
    } bits;
} RecordHeader;

typedef struct RecordEntry {
    RecordHeader header;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct ItemDef {
    int handle;
    int kind;
    u32 maxValue;
    u32 unknown0c;
    u32 iconIndex;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u16 unknown06;
    ItemDef *def;
} ItemStock;

typedef struct SlotPair {
    u16 first;
    u16 second;
} SlotPair;

typedef struct SaveData {
    u8 unknown0000[0x2bd8];
    u32 ownedFlags[(0x2d84 - 0x2bd8) / 4];
    SlotPair slots[8];
    u8 unknown2da4[0x2dc0 - 0x2da4];
    u32 equippedProgress[8];
    u16 category4Values[16];
} SaveData;

typedef struct MessageWindowStorage {
    u8 unknown[0x9c64];
} MessageWindowStorage;

typedef struct MenuPanel {
    int mode;
    int state;
    int closing;
    u8 unknown000c[0x34 - 0xc];
    MenuImage itemIcons[(0x670 - 0x34) / 12];
    MenuImage leftBorder;
    MenuImage rightBorder;
    MenuImage ownershipIcon;
    MenuImage maximumIcon;
    MenuImage equippedIcon;
    MenuImage gaugeImage;
    MenuImage rankIcons[5];
    u8 unknown06f4[0x3c18 - 0x6f4];
    ItemStock *items[(0x4d84 - 0x3c18) / 4];
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
    u8 rowHeight;
    u8 unknown4d8d[0x4db8 - 0x4d8d];
    int scrollPixels;
    u8 unknown4dbc[0x7f9c - 0x4dbc];
    MessageWindowStorage messageWindow;
    u8 unknown11c00[0x11e5c - 0x11c00];
    int lastVBlankState;
    u8 unknown11e60[4];
    u32 ownedFlags[16];
} MenuPanel;

enum { MenuItemsOffset = (u32)&((MenuPanel *)0)->items };

#define CHECK_ROW_OFFSET(type, member, offset, label) \
    typedef char label[(u32)&((type *)0)->member == (offset) ? 1 : -1]
typedef char RecordHeaderIsTwoBytes[sizeof(RecordHeader) == 2 ? 1 : -1];
typedef char RecordEntryIsFourBytes[sizeof(RecordEntry) == 4 ? 1 : -1];
typedef char ItemStockIsTwelveBytes[sizeof(ItemStock) == 12 ? 1 : -1];
typedef char ImageQuadIsTwentyFourBytes[sizeof(ImageQuad) == 24 ? 1 : -1];
CHECK_ROW_OFFSET(MenuPanel, itemIcons, 0x34, RowIconOffset);
CHECK_ROW_OFFSET(MenuPanel, leftBorder, 0x670, LeftBorderOffset);
CHECK_ROW_OFFSET(MenuPanel, ownershipIcon, 0x688, OwnershipIconOffset);
CHECK_ROW_OFFSET(MenuPanel, rankIcons, 0x6b8, RankIconsOffset);
CHECK_ROW_OFFSET(MenuPanel, items, 0x3c18, RowItemsOffset);
CHECK_ROW_OFFSET(MenuPanel, itemCount, 0x4d84, RowItemCountOffset);
CHECK_ROW_OFFSET(MenuPanel, topIndex, 0x4d88, RowTopIndexOffset);
CHECK_ROW_OFFSET(MenuPanel, rowHeight, 0x4d8c, RowHeightOffset);
CHECK_ROW_OFFSET(MenuPanel, scrollPixels, 0x4db8, RowScrollPixelsOffset);
CHECK_ROW_OFFSET(MenuPanel, messageWindow, 0x7f9c, RowMessageWindowOffset);
CHECK_ROW_OFFSET(MenuPanel, lastVBlankState, 0x11e5c, RowLastVBlankStateOffset);
CHECK_ROW_OFFSET(MenuPanel, ownedFlags, 0x11e64, RowOwnedFlagsOffset);
CHECK_ROW_OFFSET(SaveData, ownedFlags, 0x2bd8, SaveOwnedFlagsOffset);
CHECK_ROW_OFFSET(SaveData, slots, 0x2d84, SaveSlotsOffset);
CHECK_ROW_OFFSET(SaveData, equippedProgress, 0x2dc0, SaveEquippedProgressOffset);
CHECK_ROW_OFFSET(SaveData, category4Values, 0x2de0, SaveCategoryValuesOffset);
#undef CHECK_ROW_OFFSET

extern const CellGrid data_ov076_020cd12c;
extern SaveData *data_0205fe0c;
extern int func_01ff80d4(void);
extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern ItemStock *CommandMatrix_GetStockForRecord(MenuPanel *panel, const RecordEntry *record);
extern int GetPackedBitMask(const u32 *words, int bit);
extern ImageQuad *InitGridImageQuad_020c97b4(ImageQuad *quad, const MenuImage *image,
                                         s16 x, s16 y, fx32 depth, u16 color, CellGrid grid);
extern ImageQuad *InitImageQuad_020c9790(ImageQuad *quad, const MenuImage *image,
                                     s16 x, s16 y, fx32 depth, u16 color);
extern void DrawImageQuad_020c9a78(const ImageQuad *quad, BOOL decal);
extern void DrawMenuImageModulated_020ccf34(const MenuImage *images, u32 select,
                                         u32 position, fx32 depth);
extern void DrawSlotMenuGaugeAndDigits(MenuPanel *panel, int row, u32 value, u32 maxValue, int x);
extern BOOL MessageWindow_IsFinished(MessageWindowStorage *window);
extern void MessageWindow_Update(MessageWindowStorage *window, BOOL handleInput);
/* Legacy symbol name: this returns the supplied progress unchanged. */
extern u32 MSL_FpInitC(u32 progress);

#pragma opt_common_subs off
static inline u16 ReadRecordGaugeValue(u16 recordIndex, u32 rawHeader)
{
    SaveData *save = data_0205fe0c;
    const SlotPair *slots = save->slots;
    const u32 *values = save->equippedProgress;
    u16 result;
    if (slots[0].first == recordIndex) result = values[0];
    else if (slots[1].first == recordIndex) result = values[1];
    else if (slots[2].first == recordIndex) result = values[2];
    else if (slots[3].first == recordIndex) result = values[3];
    else if (slots[4].first == recordIndex) result = values[4];
    else if (slots[5].first == recordIndex) result = values[5];
    else if (slots[6].first == recordIndex) result = values[6];
    else if (slots[7].first == recordIndex) result = values[7];
    else result = MSL_FpInitC((rawHeader & 0xffffu) >> 5);
    return result;
}

static inline int GetItemOwnershipRow(MenuPanel *panel, int itemHandle)
{
    BOOL owned = GetPackedBitMask(data_0205fe0c->ownedFlags, itemHandle) ? TRUE : FALSE;
    BOOL marked = GetPackedBitMask(panel->ownedFlags, itemHandle) ? TRUE : FALSE;
    return owned ? 2 : (marked ? 1 : 0);
}

static inline int GetFirstDrawnRow(MenuPanel *panel)
{
    s16 requested = panel->topIndex;
    int selected = requested;
    if (requested > panel->scrollPixels / panel->rowHeight) selected = requested - 1;
    return selected;
}

void MenuPanel_DrawItemRows(MenuPanel *panel)
{
    ImageQuad quad;
    CellGrid grid = data_ov076_020cd12c;
    int y = 24 - (s16)(panel->scrollPixels & 15);
    fx32 depth = 0x3fe000;
    int top = GetFirstDrawnRow(panel);
    int row;
    ItemStock *stock;
    ItemStock *source;
    RecordEntry *record;
    ItemDef *def;
    int group;
    u32 value;

    panel->lastVBlankState = func_01ff80d4();
    if (panel->state != 0) {
        if (panel->closing == 0) {
            row = 0;
            const u8 *itemRowBase = (const u8 *)panel + top * sizeof(panel->items[0]);
            for (; row < 10; depth += 0x200, y += 16, row = (s16)(row + 1)) {
                if (top + row < panel->itemCount) {
                    stock = *(ItemStock *const *)(itemRowBase + row * sizeof(ItemStock *) + MenuItemsOffset);
                    if (stock->recordIndex < 0) {
                        record = NULL;
                    } else {
                        record = GetActiveRecordEntryOrNull((u16)stock->recordIndex);
                    }
                    if (record != NULL) {
                        source = CommandMatrix_GetStockForRecord(panel, record);
                    } else {
                        source = stock;
                    }
                    def = source->def;
                    grid.row = GetItemOwnershipRow(panel, def->handle);
                    if (grid.row < 2) {
                        DrawImageQuad_020c9a78(InitGridImageQuad_020c97b4(&quad, &panel->ownershipIcon,
                            0x50, (s16)y, depth, 0x7fff, grid), FALSE);
                    }
                    if (stock->used != 0) {
                        DrawImageQuad_020c9a78(InitImageQuad_020c9790(&quad, &panel->equippedIcon,
                            0x58, (s16)(y + 8), depth, 0x7fff), FALSE);
                    }
                    DrawMenuImageModulated_020ccf34(panel->itemIcons,
                        ((u32)(u16)def->iconIndex << 16) | 0x7fff,
                        ((u32)0x58 << 16) | (u16)(s16)y, depth);
                    if (def->kind == 4) {
                        group = def->handle - 0xd0;
                        if (group % 5 == 4) {
                            DrawImageQuad_020c9a78(InitImageQuad_020c9790(&quad, &panel->maximumIcon,
                                0xd4, (s16)(y + 1), depth, 0x7fff), FALSE);
                        } else {
                            DrawSlotMenuGaugeAndDigits(panel, row,
                                data_0205fe0c->category4Values[(u16)(group / 5)], def->maxValue, 0xd3);
                        }
                    } else if (record != NULL) {
                        if (record->level == 100) {
                            DrawImageQuad_020c9a78(InitImageQuad_020c9790(&quad, &panel->maximumIcon,
                                0xc3, (s16)(y + 1), depth, 0x7fff), FALSE);
                        }
                        const u32 rank = record->header.bits.rank;
                        if (rank != 0) {
                            DrawImageQuad_020c9a78(InitImageQuad_020c9790(&quad,
                                &panel->rankIcons[rank - 1], 0xd8, (s16)y, depth, 0x7fff), FALSE);
                        } else {
                            value = ReadRecordGaugeValue((u16)stock->recordIndex, record->header.raw);
                            DrawSlotMenuGaugeAndDigits(panel, row, value, def->maxValue, 0xd3);
                        }
                    }
                }
                DrawImageQuad_020c9a78(InitImageQuad_020c9790(&quad, &panel->leftBorder,
                    0x58, (s16)y, depth, 0x7fff), FALSE);
                DrawImageQuad_020c9a78(InitImageQuad_020c9790(&quad, &panel->rightBorder,
                    0xd8, (s16)y, depth, 0x7fff), FALSE);
            }
        } else {
            MessageWindow_Update(&panel->messageWindow, MessageWindow_IsFinished(&panel->messageWindow));
        }
    }
}
