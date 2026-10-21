#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct CellPos {
    int x;
    int y;
} CellPos;

typedef struct PanelElement {
    u16 unk_00;
    s16 x;
    s16 y;
} PanelElement;

typedef struct TextLayer {
    NNSG2dFont *font;
    u8 pad_04[0xc];
    NNSG2dTextCanvas txn;
} TextLayer;

typedef struct SaveData {
    u8 pad_0000[0x28d7];
    u8 selectedRecord : 4;
    u8 selectedPage : 4;
    u8 pad_28d8[0x2dc0 - 0x28d8];
    u32 slotValues[8];
} SaveData;

typedef struct RecordSlot {
    const u16 *name;
    const u16 *description;
    u8 state;
    u8 level;
    u8 kind;
    u8 pad_0b;
    u16 value;
    u16 pad_0e;
} RecordSlot;

typedef struct RecordPage {
    u8 count;
    u8 target;
    u8 pad_02;
    u8 dragging;
    RecordSlot entries[8];
    u8 pad_84[4];
    CellPos rowPos[5];
    PanelElement *cursor;
    void *rowWidget;
    s16 cellsA[7];
    s16 cellsB[7];
    s16 cellsC[7];
} RecordPage;

typedef struct StatusMenu {
    s8 page;
    u8 loaded;
    u8 pad_02;
    u8 flags;
    u8 pad_04[0x14 - 0x4];
    int busy;
    u8 pad_18[0xdf4 - 0x18];
    TextLayer textLayer;
    u8 pad_e14[0x10dc - 0xe14];
    void *pool;
    void *widgets;
    u8 pad_10e4[0x10f4 - 0x10e4];
    s16 listCount;
    s16 listSelected;
    s16 listTop;
    u8 pad_10fa;
    u8 listRows;
    u8 pad_10fc[0x11e0 - 0x10fc];
    s16 rowCellsD[7];
    s16 slotCells[7][4];
} StatusMenu;

extern SaveData *data_0205fe0c;
extern const u16 data_02055fd4[];
extern const char data_ov073_020c41b4[];

extern void func_0204f378(void *widgets, int index, int visible);
extern void func_0204f204(void *widgets, int index, int frame);
extern void func_0204f13c(void *widgets, int index, CellPos *pos);
extern void func_ov027_020b8284(void *pool, PanelElement *element, u8 mode);
extern void func_ov027_020b822c(void *pool, PanelElement *element, s16 x, s16 y);
extern void func_ov027_020b91c8(void *widgets, void *widget, const CellPos *pos, int mode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern NNSG2dFont *func_ov039_020bc9ac(void);
extern int G2D_MeasureTextWidth_02016bc0(const NNSG2dFont *pFont, int hSpace, const void *txt);
extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);
extern int G2D_DrawCharGlyph_02017910(const NNSG2dCharCanvas *pCC, const NNSG2dFont *pFont, int x, int y, int cl, u16 ccode);
extern int OS_SNPrintf_0202e080(void *dst, u32 len, const char *fmt, ...);
extern int FormatStateText_020bccac(int id, u16 *buffer, int size, ...);
extern void DrawTextAnchored_020015a0(TextLayer *obj, int x, int y, int color, u32 flags, const u16 *text);
extern void func_020015a0(TextLayer *obj, int x, int y, int color, u32 flags, const u16 *text);
extern void SetStatusHeaderMessage_020c1dbc(const u16 *shortText, const u16 *longText, int kind, int value);

static inline void DrawCanvasText(const NNSG2dTextCanvas *txn, int x, int y, int color, u32 flags, const void *text)
{
    const NNSG2dFont *font = txn->pFont;
    NNSiG2dTextDirection dir = {0, 0};

    switch (font->pRes->pGlyph->flags) {
    case 0:
    case 7:
        dir.x = 1;
        break;
    case 1:
    case 2:
        dir.y = 1;
        break;
    case 3:
    case 4:
        dir.x = -1;
        break;
    case 5:
    case 6:
        dir.y = -1;
        break;
    }
    G2D_DrawAnchoredText_02017dec(txn, x, y, color, flags, text, dir);
}

static inline void DrawWrapped(const NNSG2dTextCanvas *txn, int x, int y, int color, u32 flags, const void *text)
{
    DrawCanvasText(txn, x, y, color, flags, text);
}

static inline void PlaceRowCells(void *widgets, StatusMenu *menu, RecordPage *page, int row, CellPos *pos)
{
    func_0204f13c(widgets, page->cellsA[row], &pos[0]);
    func_0204f13c(widgets, page->cellsB[row], &pos[1]);
    func_0204f13c(widgets, page->cellsC[row], &pos[2]);
    func_0204f13c(widgets, menu->rowCellsD[row], &pos[3]);
    func_0204f13c(widgets, menu->slotCells[row][0], &pos[4]);
    func_0204f13c(widgets, menu->slotCells[row][1], &pos[5]);
    func_0204f13c(widgets, menu->slotCells[row][2], &pos[6]);
    func_0204f13c(widgets, menu->slotCells[row][3], &pos[7]);
}

void DrawRecordSlotRows_020c06f0(StatusMenu *menu, RecordPage *page)
{
    int y;
    RecordSlot *entries;
    TextLayer *layer;
    void *widgets;
    void *pool;
    int row;
    int selected;
    int x;
    const u16 *name;
    int kind;
    u16 glyph;
    int width;
    BOOL highlight;
    int selectedRecord;
    int dragOffset;
    int count;
    CellPos *rowPos;
    int firstX;
    int glyphColor;
    int i;
    RecordSlot *entry;
    u16 slot;
    int shift;
    BOOL maxed;
    CellPos pos[8];
    u16 buffer[32];

    layer = &menu->textLayer;
    widgets = menu->widgets;
    pool = menu->pool;
    selectedRecord = data_0205fe0c->selectedRecord;
    selected = menu->listSelected;
    dragOffset = page->dragging << 16;
    count = menu->listCount > menu->listRows ? menu->listRows : menu->listCount;
    rowPos = page->rowPos;
    /* Partial init keeps the glyph colour unfolded */
    if (rowPos) {
        glyphColor = 10;
    }
    firstX = rowPos->x;
    pos[0].y = page->rowPos[0].y;
    pos[0].x = firstX;
    pos[1] = page->rowPos[1];
    pos[2] = page->rowPos[2];
    pos[3] = page->rowPos[3];
    pos[4] = page->rowPos[4];
    pos[5] = pos[4];
    pos[5].x -= 0x4000;
    pos[6] = pos[5];
    pos[6].x -= 0x4000;
    pos[7] = pos[6];
    pos[7].x -= 0x4000;
    row = menu->listTop;
    for (i = 0; i < count; i++) {
        entries = page->entries;
        slot = row;
        highlight = FALSE;
        if (page->dragging && selected == row) {
            highlight = TRUE;
        }
        func_0204f378(widgets, page->cellsA[i], 1);
        func_ov027_020b8284(pool, page->cursor, selectedRecord == row ? 7 : 3);
        func_ov027_020b822c(pool, page->cursor, page->cursor->x - highlight * 2, page->cursor->y + i * 2);
        if (page->dragging) {
            if (row == selected) {
                slot = page->target;
                entries = page->entries;
            } else if (selected > page->target) {
                if (row < selected) {
                    slot++;
                }
                if (row < page->target) {
                    slot--;
                }
            } else if (page->target > selected) {
                if (selected < row) {
                    slot--;
                }
                if (page->target < row) {
                    slot++;
                }
            }
        }
        entry = &entries[slot];
        func_0204f204(widgets, page->cellsA[i], slot);
        if (highlight) {
            pos[0].x -= dragOffset;
            pos[1].x -= dragOffset;
            pos[2].x -= dragOffset;
            pos[3].x -= dragOffset;
            pos[4].x -= dragOffset;
            pos[5].x -= dragOffset;
            pos[6].x -= dragOffset;
            pos[7].x -= dragOffset;
        }
        PlaceRowCells(widgets, menu, page, i, pos);
        if (highlight) {
            pos[0].x += dragOffset;
            pos[1].x += dragOffset;
            pos[2].x += dragOffset;
            pos[3].x += dragOffset;
            pos[4].x += dragOffset;
            pos[5].x += dragOffset;
            pos[6].x += dragOffset;
            pos[7].x += dragOffset;
        }
        shift = highlight ? dragOffset >> 12 : 0;
        if (entry->name != NULL) {
            maxed = entry->state != 2 && entry->level >= 100;
            y = i * 16;
            func_0204f378(widgets, page->cellsB[i], 1);
            func_0204f378(widgets, page->cellsC[i], maxed);
            func_0204f204(widgets, page->cellsB[i], entry->state);
            kind = entry->kind;
            name = entry->name;
            x = 0x36 - shift;
            layer->txn.pFont = func_ov039_020bc994();
            width = G2D_MeasureTextWidth_02016bc0(layer->txn.pFont, layer->txn.hSpace, name);
            if (width >= 0x56) {
                layer->txn.pFont = func_ov039_020bc9ac();
                width = G2D_MeasureTextWidth_02016bc0(layer->txn.pFont, layer->txn.hSpace, name);
            }
            DrawWrapped(&layer->txn, x + 1, y + 3, 3, 0, name);
            DrawCanvasText(&layer->txn, x, y + 2, 2, 0, name);
            if (kind != 0) {
                glyph = data_02055fd4[kind];
                x += width;
                G2D_DrawCharGlyph_02017910(layer->txn.pCanvas, layer->txn.pFont, x + 1, y + 3, glyphColor + 1, glyph);
                G2D_DrawCharGlyph_02017910(layer->txn.pCanvas, layer->txn.pFont, x, y + 2, glyphColor, glyph);
            }
            if (entry->state != 2) {
                if (entry->level != 0 && entry->level < 100) {
                    int valueX;

                    layer->font = func_ov039_020bc994();
                    FormatStateText_020bccac(1, buffer, 0x20, entry->level);
                    valueX = 0xb6 - shift;
                    func_020015a0(layer, valueX + 1, y + 3, 3, 0x20, buffer);
                    func_020015a0(layer, valueX, y + 2, 2, 0x20, buffer);
                }
            } else {
                int valueX;

                layer->font = func_ov039_020bc994();
                OS_SNPrintf_0202e080(buffer, 0x20, data_ov073_020c41b4, data_0205fe0c->slotValues[slot]);
                valueX = 0xb6 - shift;
                DrawTextAnchored_020015a0(layer, valueX + 1, y + 3, 3, 0x20, buffer);
                DrawTextAnchored_020015a0(layer, valueX, y + 2, 2, 0x20, buffer);
            }
        } else {
            func_0204f378(widgets, page->cellsB[i], 0);
            func_0204f378(widgets, page->cellsC[i], 0);
        }
        pos[0].y += 0x10000;
        pos[1].y += 0x10000;
        pos[2].y += 0x10000;
        pos[3].y += 0x10000;
        pos[4].y += 0x10000;
        pos[5].y += 0x10000;
        pos[6].y += 0x10000;
        pos[7].y += 0x10000;
        row++;
    }
    if (i < 7) {
        for (; i < 7; i++) {
            func_0204f378(widgets, page->cellsA[i], 0);
            func_0204f378(widgets, page->cellsB[i], 0);
            func_0204f378(widgets, page->cellsC[i], 0);
        }
    }
    pos[0].y = (menu->listSelected - menu->listTop) << 16;
    pos[0].x = -dragOffset;
    func_ov027_020b91c8(menu->widgets, page->rowWidget, &pos[0], 3);
    if (menu->busy != 0 && (menu->flags & 2)) {
        int index;

        if (page->dragging) {
            index = page->target;
        } else {
            index = menu->listSelected;
        }
        SetStatusHeaderMessage_020c1dbc(NULL, page->entries[index].description, 4, 0);
    }
}
