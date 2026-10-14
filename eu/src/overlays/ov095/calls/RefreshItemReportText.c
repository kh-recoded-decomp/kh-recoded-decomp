#include "nitro/types.h"

typedef struct ItemReportRoute {
    u32 kind;
    int id;
} ItemReportRoute;

typedef struct ItemReportTextLayer {
    u8 state[0x34];
} ItemReportTextLayer;

typedef struct ItemReportTextBank {
    void *archive;
    u32 count;
    void *data;
} ItemReportTextBank;

typedef struct ItemReportGridState {
    u8 unknown_00[0x20];
    u32 *cells;
    int width;
    u8 unknown_28[8];
    int cursor;
    int scrollPixels;
} ItemReportGridState;

typedef struct ItemReportMenu {
    int selectedIndex;
    u8 unknown_00004[0x20 - 4];
    ItemReportTextLayer summary;
    ItemReportTextLayer labels;
    ItemReportTextLayer title;
    ItemReportTextLayer description;
    u8 unknown_000f0[0x110a4 - 0xf0];
    ItemReportGridState grid;
    u8 unknown_110dc[12];
    ItemReportTextBank labelBank;
    ItemReportTextBank detailBank;
    u8 unknown_11100[8];
    BOOL detailOpen;
    u8 unknown_1110c[12];
    const u16 *itemName;
    const u16 *itemDescription;
    int detailKind;
} ItemReportMenu;

typedef struct ItemReportRecord {
    u32 unknown_00;
    int kind;
    u8 unknown_08[0x40 - 8];
    const u16 *name;
    const u16 *description;
} ItemReportRecord;

typedef struct ItemReportSecondaryRecord {
    u8 unknown_00[0x28];
    const u16 *name;
    const u16 *description;
} ItemReportSecondaryRecord;

typedef struct ItemReportRecipe {
    u32 unknown_00;
    int firstItem;
    int secondItem;
    int resultItem;
} ItemReportRecipe;

typedef struct ItemReportGridEntry {
    int id;
} ItemReportGridEntry;

extern u32 gItemReportIdentifiers[];
extern u16 data_ov095_020c28cc[];
extern ItemReportRecord *GetRecordSlotPair0Entry(int);
extern ItemReportSecondaryRecord *GetRecordSlotPair1Entry(int);
extern ItemReportRecipe *GetRecordSlot6Entry(int);
extern int SPrintfUnbounded(u16 *, const u16 *, ...);
extern void *func_ov027_020ba2c8(ItemReportTextBank *, int);
extern void CallVirtualHandlerSlot1(ItemReportTextLayer *, int);
extern void Text_UploadTileBuffer(ItemReportTextLayer *);
extern void DrawShadowedAnchoredText_020c0000(ItemReportTextLayer *, int, int, int, u32, const void *);
extern void DrawShadowedTextFitted(ItemReportTextLayer *, u32, u32, u32, u32, const void *, int);
extern void func_ov095_020c0064(ItemReportTextLayer *, int, int, int, int, const void *);
extern u32 GetGridCell(int, int, ItemReportMenu *);
extern BOOL IsEntryFlagSet_020c1340(int, int);

void RefreshItemReportText(int refresh, ItemReportMenu *menu)
{
    u16 recipes[10][50];
    ItemReportTextBank *labelBank = &menu->labelBank;
    ItemReportTextBank *detailBank = &menu->detailBank;
    ItemReportRecord *record;
    ItemReportRecipe *recipe;
    ItemReportSecondaryRecord *secondary;
    int recipeCount = 0;
    BOOL showRecipeLabel = FALSE;
    /* The table stores two words per report: its source kind and record id. */
    const ItemReportRoute *route = (const ItemReportRoute *)gItemReportIdentifiers + menu->selectedIndex;
    int resultId;
    int i;
    const u16 *firstName;
    const void *text;
    int y;
    int columns;
    int selectedCell;
    int id;

    menu->detailKind = 0;
    switch (route->kind) {
    case 0:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        resultId = route->id;
        record = GetRecordSlotPair0Entry(resultId);
        menu->itemName = record->name;
        menu->itemDescription = record->description;
        switch (route->kind) {
        case 3:
        case 4:
            menu->detailKind = 2;
            break;
        }
        switch (record->kind) {
        case 2:
        case 3: {
            for (i = 0; i < 333; i++) {
                recipe = GetRecordSlot6Entry(i);
                if (recipe->resultItem == resultId) {
                    firstName = GetRecordSlotPair0Entry(recipe->firstItem)->name;
                    SPrintfUnbounded(recipes[recipeCount], data_ov095_020c28cc,
                                     firstName, GetRecordSlotPair0Entry(recipe->secondItem)->name);
                    recipeCount++;
                    menu->detailKind = 1;
                    if (recipeCount >= 10) break;
                }
            }
            /* Recipe-capable entries show the header even when no recipe was found. */
            showRecipeLabel = TRUE;
            break;
        }
        }
        break;
    case 1:
        secondary = GetRecordSlotPair1Entry(route->id);
        menu->itemName = secondary->name;
        menu->itemDescription = secondary->description;
        break;
    case 2:
        menu->itemName = func_ov027_020ba2c8(detailBank, route->id);
        menu->itemDescription = func_ov027_020ba2c8(detailBank, route->id + 1);
        break;
    }

    /* -1 refreshes both screens; 0 refreshes labels, and 1 refreshes details. */
    if ((u32)(refresh + 1) <= 1) {
        text = func_ov027_020ba2c8(labelBank, 1);
        CallVirtualHandlerSlot1(&menu->summary, 0);
        if (showRecipeLabel) {
            DrawShadowedAnchoredText_020c0000(&menu->summary, 4, 2, 3, 0, text);
        }
        Text_UploadTileBuffer(&menu->summary);
        y = 4 - menu->grid.scrollPixels;
        CallVirtualHandlerSlot1(&menu->labels, 0);
        DrawShadowedAnchoredText_020c0000(&menu->labels, 4, y, 5, 0,
                                         func_ov027_020ba2c8(labelBank, 2));
        DrawShadowedAnchoredText_020c0000(&menu->labels, 4, y + 0x70, 5, 0,
                                         func_ov027_020ba2c8(labelBank, 3));
        DrawShadowedAnchoredText_020c0000(&menu->labels, 4, y + 0xc0, 5, 0,
                                         func_ov027_020ba2c8(labelBank, 4));
        DrawShadowedAnchoredText_020c0000(&menu->labels, 4, y + 0xf0, 5, 0,
                                         func_ov027_020ba2c8(labelBank, 5));
        DrawShadowedAnchoredText_020c0000(&menu->labels, 4, y + 0x160, 5, 0,
                                         func_ov027_020ba2c8(labelBank, 6));
        DrawShadowedAnchoredText_020c0000(&menu->labels, 4, y + 0x1b0, 5, 0,
                                         func_ov027_020ba2c8(labelBank, 7));
        DrawShadowedAnchoredText_020c0000(&menu->labels, 4, y + 0x1e0, 5, 0,
                                         func_ov027_020ba2c8(labelBank, 8));
        DrawShadowedAnchoredText_020c0000(&menu->labels, 4, y + 0x210, 5, 0,
                                         func_ov027_020ba2c8(labelBank, 9));
        DrawShadowedAnchoredText_020c0000(&menu->labels, 4, y + 0x250, 5, 0,
                                         func_ov027_020ba2c8(labelBank, 10));
        Text_UploadTileBuffer(&menu->labels);
    }
    if (refresh != 1 && refresh != -1) return;

    ItemReportGridState *grid = &menu->grid;
    columns = grid->width;
    selectedCell = grid->cursor;
    id = ((ItemReportGridEntry *)GetGridCell(selectedCell % columns,
                                            selectedCell / columns, menu))->id;
    if (!menu->detailOpen) {
        CallVirtualHandlerSlot1(&menu->title, 0);
        if (IsEntryFlagSet_020c1340(0, id)) text = menu->itemName;
        else text = func_ov027_020ba2c8(labelBank, 11);
        DrawShadowedTextFitted(&menu->title, 4, 4, 3, 0, text, 104);
        Text_UploadTileBuffer(&menu->title);
        CallVirtualHandlerSlot1(&menu->description, 0);
        if (IsEntryFlagSet_020c1340(0, id)) {
            func_ov095_020c0064(&menu->description, 0, 4, 1, 8, menu->itemDescription);
        }
        Text_UploadTileBuffer(&menu->description);
        return;
    }

    text = func_ov027_020ba2c8(labelBank, 12);
    int rowY;
    int line = 0;
    CallVirtualHandlerSlot1(&menu->title, 0);
    rowY = 4;
    DrawShadowedAnchoredText_020c0000(&menu->title, rowY, rowY, 3, 0, text);
    Text_UploadTileBuffer(&menu->title);
    CallVirtualHandlerSlot1(&menu->description, 0);
    if (menu->detailKind == 1) {
        if (IsEntryFlagSet_020c1340(0, id)) {
            for (; line < recipeCount; line++, rowY += 16) {
                DrawShadowedAnchoredText_020c0000(&menu->description, 0, rowY, 1, 0, recipes[line]);
            }
        } else {
            DrawShadowedAnchoredText_020c0000(&menu->description, 0, 4, 1, 0,
                                             func_ov027_020ba2c8(labelBank, 11));
        }
    } else {
        if (IsEntryFlagSet_020c1340(0, id)) {
            text = func_ov027_020ba2c8(labelBank, 13);
        } else {
            text = func_ov027_020ba2c8(labelBank, 11);
        }
        DrawShadowedAnchoredText_020c0000(&menu->description, 0, 4, 1, 0, text);
    }
    Text_UploadTileBuffer(&menu->description);
}
