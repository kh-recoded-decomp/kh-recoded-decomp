#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CellAnchor {
    u8 pad_00[2];
    s16 x;
    s16 y;
} CellAnchor;

typedef struct StatusItem {
    u32 unk_00;
    const u16 *name;
    const u16 *description;
    u16 valueText[8];
    BOOL highlighted;
} StatusItem;

typedef struct ItemContent {
    u32 unk_000;
    StatusItem items[0x40];
    CellAnchor *rowAnchor;
    void *cursorWidget;
} ItemContent;

typedef struct TextLayer {
    void *font;
} TextLayer;

typedef struct StatusMenu {
    s8 page;
    u8 pad_01[2];
    u8 flags;
    u8 pad_04[0x14 - 0x04];
    BOOL active;
    u8 pad_18[0xdf4 - 0x18];
    TextLayer textLayer;
    u8 pad_df8[0x10dc - 0xdf8];
    void *recordPool;
    void *container;
    u8 pad_10e4[0x10f4 - 0x10e4];
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
} StatusMenu;

extern void func_ov027_020b822c(void *pool, CellAnchor *anchor, int x, s16 y);
extern BOOL SetTextColorIfFits_020bcd04(TextLayer *layer, int limit, const u16 *text);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void *func_ov039_020bc994(void);
extern void func_ov027_020b91c8(void *container, void *element, fx32 *position, int mode);
extern void SetStatusHeaderText_020c1d38(const u16 *shortText, const u16 *longText);

void DrawStatusItemRows_020c0eb8(StatusMenu *menu, ItemContent *content)
{
    void *pool = menu->recordPool;
    int index;
    const u16 *text;
    int count;
    int row;
    StatusItem *item;
    int color;
    const u16 *description;
    fx32 position[2];

    count = menu->visibleRows;
    if (menu->itemCount <= count) {
        count = menu->itemCount;
    }
    index = menu->topIndex;
    for (row = 0; row < count; row++) {
        item = &content->items[index];
        func_ov027_020b822c(pool, content->rowAnchor, content->rowAnchor->x, content->rowAnchor->y + row * 2);
        SetTextColorIfFits_020bcd04(&menu->textLayer, 0x84, item->name);
        text = item->name;
        DrawTextAnchored_020015a0(&menu->textLayer, 0x25, row * 16 + 3, 3, 8, text);
        DrawTextAnchored_020015a0(&menu->textLayer, 0x24, row * 16 + 2, 2, 8, text);
        if (item->valueText[0] != 0) {
            ((TextLayer *)(u32)&menu->textLayer)->font = func_ov039_020bc994();
            if (item->highlighted) {
                color = 10;
            } else {
                color = 2;
            }
            DrawTextAnchored_020015a0(&menu->textLayer, 0xb5, row * 16 + 3, color + 1, 0x20, item->valueText);
            DrawTextAnchored_020015a0(&menu->textLayer, 0xb4, row * 16 + 2, color, 0x20, item->valueText);
        }
        index++;
    }
    if (row == 0) {
        description = NULL;
        position[1] = 0;
        func_ov027_020b822c(pool, content->rowAnchor, content->rowAnchor->x, content->rowAnchor->y);
    } else {
        position[1] = (menu->cursor - menu->topIndex) << 16;
        description = content->items[menu->cursor].description;
    }
    func_ov027_020b91c8(menu->container, content->cursorWidget, position, 5);
    if (menu->active && (menu->flags & 2)) {
        SetStatusHeaderText_020c1d38(NULL, description);
    }
}
