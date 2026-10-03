#include "nitro/types.h"

typedef struct {
    s32 width;
    s32 height;
} TextSize;

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct {
    s32 count;
    u32 unk_04;
    const void **strings;
    u32 unk_0C;
    TextWindow *windows;
    u16 maxWidth;
    u16 maxHeight;
    u16 visibleRows;
    u16 pageCount;
    u16 rowsPerPage;
    u16 scroll;
    u16 top;
    u16 left;
    u16 space;
} ChoiceList;

typedef struct {
    s32 mode;
    u8 pad_04[0xe];
    u16 baseRow;
    u8 pad_14[0x2];
    u16 rowCount;
    u8 pad_18[0x3c];
    ChoiceList list;
} ChoiceMenu;

extern void *GetFieldFont3_020711e0(void);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern int MeasureMessageTiles_02078dd8(TextSize *size, BOOL useFixedSize, const void *font, const void *text);
extern int func_02023dbc(int numerator, int denominator);
extern void InitTextLayerAt_020014b0(void *window, int bgLayer, void *charBase, void *font, TextFrame *frame);
extern void DrawTextAnchored_020015a0(void *window, int x, int y, int color, int flags, const void *text);
extern void FlushBufferAndRunCallback_0200153c(void *window);

void BuildChoiceListWindows_02078e30(ChoiceMenu *menu) {
    ChoiceList *list = &menu->list;
    void *font = GetFieldFont3_020711e0();
    TextSize size;
    TextFrame frame;
    u16 rows;
    int charBase;
    int tileCount;
    int i;

    list->windows = NNSi_FndAllocFromDefaultHeapEx_0202a19c(menu->list.count * sizeof(TextWindow), -4);
    list->maxWidth = 0;
    list->maxHeight = 0;
    for (i = 0; i < list->count; i++) {
        MeasureMessageTiles_02078dd8(&size, FALSE, font, list->strings[i]);
        list->maxWidth = list->maxWidth >= size.width ? list->maxWidth : size.width;
        list->maxHeight = list->maxHeight >= size.height + 1 ? list->maxHeight : size.height + 1;
    }
    switch (menu->mode) {
    case 1:
        list->top = 0;
        list->space = 0x16 - menu->rowCount;
        break;
    case 2:
        list->top = 0;
        list->space = 0;
        break;
    default:
        list->top = menu->baseRow + menu->rowCount + 2;
        list->space = 0x18 - list->top;
        break;
    }
    list->scroll = 0;
    list->left = 0x20;
    rows = func_02023dbc(list->space, 5);
    list->rowsPerPage = 1;
    list->pageCount = func_02023dbc(list->count + list->rowsPerPage - 1, list->rowsPerPage);
    if (rows > list->pageCount) {
        rows = list->pageCount;
    }
    list->visibleRows = rows;
    frame.x = 0;
    frame.y = 0;
    frame.width = list->maxWidth == 0 ? 1 : list->maxWidth;
    frame.height = list->maxHeight == 0 ? 1 : list->maxHeight;
    frame.hSpace = 0;
    frame.vSpace = 3;
    frame.palette = 0xf;
    charBase = 0x98;
    tileCount = list->maxWidth * list->maxHeight;
    if (tileCount == 0) {
        tileCount = 1;
    }
    for (i = 0; i < list->count; i++) {
        TextWindow *window = &list->windows[i];

        frame.charBase = charBase;
        InitTextLayerAt_020014b0(window, 2, NULL, font, &frame);
        DrawTextAnchored_020015a0(window, 3, list->maxHeight * 8 / 2, 7, 0x20a, list->strings[i]);
        DrawTextAnchored_020015a0(window, 2, list->maxHeight * 8 / 2 - 1, 8, 0x20a, list->strings[i]);
        FlushBufferAndRunCallback_0200153c(window);
        charBase += tileCount;
    }
}
