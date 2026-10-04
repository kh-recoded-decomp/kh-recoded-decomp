#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct ItemLabelInfo
{
    u8 pad_00[0x40];
    const void *text;
} ItemLabelInfo;

typedef struct ItemEntry
{
    u8 pad_00[4];
    s16 recordId;
    u8 pad_06[2];
    ItemLabelInfo *info;
} ItemEntry;

typedef struct ItemStatus
{
    int value;
    u8 pad_04[2];
    s8 rank;
} ItemStatus;

typedef struct ItemSlot
{
    u8 pad_00[8];
    ItemStatus *status;
} ItemSlot;

typedef struct ItemMenu
{
    u8 pad_00[2];
    u8 hideRank;
    u8 pad_03[0x165];
    NNSG2dTextCanvas canvas;
    u8 pad_178[0x5a4c - 0x178];
    ItemSlot *slots[1];
} ItemMenu;

typedef struct RecordEntry
{
    u16 rank : 2;
} RecordEntry;

extern ItemEntry *func_ov085_020bf72c(ItemMenu *menu, int index);
extern NNSG2dFont *func_ov039_020bc9ac(void);
extern int G2D_MeasureTextWidth_02016bc0(const NNSG2dFont *pFont, int hSpace, const void *txt);
extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);
extern int G2D_DrawCharGlyph_02017910(const NNSG2dCharCanvas *pCC, const NNSG2dFont *pFont, int x, int y, int cl, u16 ccode);
extern RecordEntry *GetActiveRecordEntryOrNull_02029548(int index);
extern u16 data_02055fd4[];

static inline NNSiG2dTextDirection GetTextDirection(const NNSG2dFont *font)
{
    NNSiG2dTextDirection dir = {0, 0};

    switch (font->pRes->pGlyph->flags)
    {
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

void DrawItemNameWithRank_020c11e8(ItemMenu *menu, int index, int x, int y, int color)
{
    ItemEntry *entry = func_ov085_020bf72c(menu, index);
    NNSG2dTextCanvas *canvas = &menu->canvas;
    u32 rank = 0;
    const void *text = entry->info->text;
    int width = G2D_MeasureTextWidth_02016bc0(canvas->pFont, canvas->hSpace, text);
    NNSG2dFont *savedFont = canvas->pFont;

    if (width >= 0x45)
    {
        canvas->pFont = func_ov039_020bc9ac();
        width = G2D_MeasureTextWidth_02016bc0(canvas->pFont, canvas->hSpace, text);
    }

    G2D_DrawAnchoredText_02017dec(canvas, x, y, color, 0, text, GetTextDirection(canvas->pFont));

    if (entry->recordId >= 0)
    {
        rank = GetActiveRecordEntryOrNull_02029548((u16)entry->recordId)->rank;
    }
    else if (menu->hideRank == 0)
    {
        ItemStatus *status = menu->slots[index]->status;
        if (status->value >= 0 && status->value <= 0x7f)
        {
            rank = status->rank + 1;
        }
    }

    if (rank != 0)
    {
        G2D_DrawCharGlyph_02017910(canvas->pCanvas, canvas->pFont, x + width, y, color == 2 ? 10 : color, data_02055fd4[rank]);
    }
    canvas->pFont = savedFont;
}
