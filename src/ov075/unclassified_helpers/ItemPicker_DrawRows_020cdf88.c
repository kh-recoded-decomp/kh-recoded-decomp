#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 unk_00_2 : 14;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct {
    int id;
    int type;
    u8 pad_08[0x38];
    const void *name;
} ItemDef;

typedef struct {
    u16 total;
    u16 used;
    s16 recordIndex;
    u16 pad_06;
    ItemDef *def;
} ItemSlot;

typedef struct {
    u8 pad_00000[0x3c18];
    ItemSlot *slots[0x45b];
    s16 slotCount;
    s16 cursor;
    s16 top;
    u8 pad_4d8a;
    u8 visibleRows;
    u8 rowHeight;
    u8 pad_4d8d[0x4db8 - 0x4d8d];
    int scroll;
    u8 pad_4dbc[0x7268 - 0x4dbc];
    NNSG2dCharCanvas charCanvas;
    NNSG2dTextCanvas textCanvas;
    u8 pad_7290[0x7f94 - 0x7290];
    int selectedId;
    s16 selectedRecord;
    u8 pad_7f9a[0x11e24 - 0x7f9a];
    u8 filterCount;
    u8 pad_11e25[3];
    u32 filterIds[0x1f];
    int *ownedBits;
} ItemPicker;

extern const u16 data_02055fd4[];
extern const char data_ov075_020d1868[];

extern RecordEntry *GetActiveRecordEntryOrNull_02029548(int index);
extern ItemSlot *MatrixMenu_GetStockForRecord_020d0f34(ItemPicker *picker, RecordEntry *record);
extern BOOL IsItemSlotAvailable_020cdf10(ItemSlot *slot, u32 count, u32 *ids);
extern int GetPackedBitMask(int *bitWords, int bitIndex);
extern NNSG2dFont *func_ov039_020bc994(void);
extern NNSG2dFont *func_ov039_020bc9ac(void);
extern int G2D_MeasureTextWidth_02016bc0(const NNSG2dFont *pFont, int hSpace, const void *txt);
extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);
extern int G2D_DrawCharGlyph_02017910(const NNSG2dCharCanvas *pCC, const NNSG2dFont *pFont, int x, int y, int cl, u16 ccode);
extern void *OS_SNPrintf_0202e080(char *dst, unsigned int len, const char *fmt, ...);
extern int FormatStateText_020bccac(int id, char *buffer, int size, ...);
extern void UpdateItemDescription_020cd384(ItemPicker *picker);

static inline NNSiG2dTextDirection GetTextDirection(const NNSG2dFont *pFont)
{
    NNSiG2dTextDirection dir = {0, 0};

    switch (pFont->pRes->pGlyph->flags) {
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
    return dir;
}

static inline void DrawText(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt)
{
    G2D_DrawAnchoredText_02017dec(pTxn, x, y, cl, flags, txt, GetTextDirection(pTxn->pFont));
}

static inline BOOL ShowsRemainingCount(ItemDef *def)
{
    if (def->type == 10) {
        switch (def->id) {
        case 0x160:
        case 0x161:
        case 0x164:
        case 0x188:
            return TRUE;
        }
        return FALSE;
    }
    return ((1 << def->type) & ~0x7c) != 0;
}

void ItemPicker_DrawRows_020cdf88(ItemPicker *picker)
{
    u16 row;
    u16 visible;
    ItemSlot **slotPtr;
    const void *name;
    ItemSlot *slot;
    s16 remaining;
    int maxWidth;
    int width;
    int baseY;
    s16 y;
    ItemSlot *source;
    int mark;
    int color;
    int top;
    int remainingRows;
    RecordEntry *record;
    BOOL selected;
    char text[0x42];
    int textX;

    visible = picker->visibleRows + 1;
    top = picker->top;
    slotPtr = &picker->slots[top];
    baseY = (s16)(3 - (picker->scroll & 0xf));
    remainingRows = picker->slotCount - top;
    if (remainingRows < visible) {
        visible = remainingRows;
    }
    if (top > picker->scroll / picker->rowHeight) {
        baseY = (s16)(baseY + 0x10);
    }
    picker->charCanvas.vtable->pClear(&picker->charCanvas, 0);
    for (row = 0; row < visible; row++, slotPtr++) {
        {
            slot = *slotPtr;
            if (slot->recordIndex < 0) {
                record = NULL;
            } else {
                record = GetActiveRecordEntryOrNull_02029548((u16)slot->recordIndex);
            }
            if (record != NULL) {
                source = MatrixMenu_GetStockForRecord_020d0f34(picker, record);
            } else {
                source = slot;
            }
            y = baseY + row * 16;
            remaining = slot->total - slot->used;
            selected = FALSE;
            if (slot->def->id == picker->selectedId && slot->recordIndex == picker->selectedRecord) {
                selected = TRUE;
            }
            if (selected) {
                color = 8;
            } else if (slot->def->type == 0) {
                color = 6;
            } else if (IsItemSlotAvailable_020cdf10(slot, picker->filterCount, picker->filterIds)) {
                if (picker->ownedBits != NULL && record != NULL && GetPackedBitMask(picker->ownedBits, record->category)) {
                    color = 0xc;
                } else {
                    color = 2;
                }
            } else {
                color = 4;
            }
            name = source->def->name;
            mark = (u8)(record != NULL ? record->kind : 0);
            switch (source->def->type) {
            case 2:
            case 3:
                maxWidth = 0x45;
                break;
            case 4:
                maxWidth = 0x62;
                break;
            case 5:
            case 6:
                maxWidth = 0x6e;
                break;
            default:
                maxWidth = 0x4f;
                break;
            }
            picker->textCanvas.pFont = func_ov039_020bc994();
            width = G2D_MeasureTextWidth_02016bc0(picker->textCanvas.pFont, picker->textCanvas.hSpace, name);
            if (width >= maxWidth) {
                picker->textCanvas.pFont = func_ov039_020bc9ac();
                width = G2D_MeasureTextWidth_02016bc0(picker->textCanvas.pFont, picker->textCanvas.hSpace, name);
            }
            textX = 4;
            DrawText(&picker->textCanvas, textX, y, color, 0, name);
            if (mark != 0) {
                textX += width;
                G2D_DrawCharGlyph_02017910(picker->textCanvas.pCanvas, picker->textCanvas.pFont, textX, y, color != 2 ? color : 10, data_02055fd4[mark]);
            }
            if (record == NULL) {
                if (ShowsRemainingCount(slot->def)) {
                    OS_SNPrintf_0202e080(text, 4, data_ov075_020d1868, remaining);
                    picker->textCanvas.pFont = func_ov039_020bc994();
                    DrawText(&picker->textCanvas, 0x69, y, color, 0x20, text);
                }
            } else if (record->level != 0 && record->level < 100) {
                FormatStateText_020bccac(1, text, 0x20, record->level);
                picker->textCanvas.pFont = func_ov039_020bc994();
                DrawText(&picker->textCanvas, 0x69, y, color, 0x20, text);
            }
        }
    }
    UpdateItemDescription_020cd384(picker);
}
