#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct ItemInfo {
    u8 pad_00[4];
    s32 type;
    u8 pad_08[0x38];
    const void *name;
} ItemInfo;

typedef struct ItemSlotEntry {
    u8 pad_00[0x8];
    ItemInfo *info;
} ItemSlotEntry;

typedef struct ItemScreen {
    u8 pad_00000[0x80c];
    ItemSlotEntry slots[1];
    u8 pad_00818[0x12004 - 0x818];
    u8 panelTiles[2][0x680];
    u8 cursorTiles[2][0x800];
    u8 labelTiles[0x680];
} ItemScreen;

typedef struct SaveState {
    u8 pad_0000[0x2c6a];
    u8 extraSlotCount;
    u8 pad_2c6b[0x2db4 - 0x2c6b];
    u16 partySlots[8];
} SaveState;

extern SaveState *data_0205fe0c;
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void func_0200344c(void *start, u32 size);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern u16 *G2_GetBG2ScrPtr_02006e88(void);
extern void FillBackgroundTileRectangle_02017adc(u16 *dst, int width, int height, int x, int y, int mapW, int tile, int palette);
extern BOOL func_ov001_020645c8(u32 value);
extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight, NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern NNSG2dFont *func_ov039_020bc9ac(void);
extern int G2D_MeasureTextWidth_02016bc0(const NNSG2dFont *pFont, int hSpace, const void *txt);
extern void G2D_DrawTextLine_02017be8(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, const void *str, const void **pNext, NNSiG2dTextDirection d);

static inline u16 GetPartySlot(int i)
{
    switch (i) {
    case 0:
        return data_0205fe0c->partySlots[0];
    case 1:
        return data_0205fe0c->partySlots[1];
    default:
        if (i >= 2 && i < data_0205fe0c->extraSlotCount + 3) {
            return data_0205fe0c->partySlots[i];
        }
        return 0xffff;
    }
}

static inline void InitTextCanvas(NNSG2dTextCanvas *pTxn, NNSG2dCharCanvas *pCC, NNSG2dFont *pFont, int hSpace, int vSpace)
{
    pTxn->pCanvas = pCC;
    pTxn->pFont = pFont;
    pTxn->hSpace = hSpace;
    pTxn->vSpace = vSpace;
}

static inline NNSiG2dTextDirection GetTextDirection(const NNSG2dFont *pFont)
{
    NNSiG2dTextDirection d = {0, 0};

    switch (pFont->pRes->pGlyph->flags) {
    case 0:
    case 7:
        d.x = 1;
        break;
    case 1:
    case 2:
        d.y = 1;
        break;
    case 3:
    case 4:
        d.x = -1;
        break;
    case 5:
    case 6:
        d.y = -1;
        break;
    }
    return d;
}

static inline void DrawText(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, const void *txt)
{
    G2D_DrawTextLine_02017be8(pTxn, x, y, cl, txt, NULL, GetTextDirection(pTxn->pFont));
}

void DrawPartySlotLabel_020c5a4c(ItemScreen *screen, int slot)
{
    NNSG2dCharCanvas canvas;
    NNSG2dTextCanvas txn;
    u16 entry = GetPartySlot(slot);
    ItemInfo *info;
    u16 color;
    const void *name;
    int width;
    int limit;
    int tile;
    int column;

    if (entry == 0xffff) {
        tile = slot * 0x1a + 0x1c8;
        if (slot < 2) {
            GX_LoadBG2Char_02007a90(screen->panelTiles[0], tile * 0x40, 0x680);
        } else {
            GX_LoadBG2Char_02007a90(screen->panelTiles[1], tile * 0x40, 0x680);
        }
        return;
    }
    if (slot < 2) {
        func_01ff878c(screen->panelTiles[0], screen->labelTiles, 0x680);
    } else {
        func_01ff878c(screen->panelTiles[1], screen->labelTiles, 0x680);
    }
    color = 0xf2;
    if (slot < 2 && func_ov001_020645c8(0x360b)) {
        color = 0xf4;
    }
    G2D_InitializeLinearCanvas_02017a2c(&canvas, screen->labelTiles, 13, 2, NNS_G2D_CHARA_COLORMODE_256);
    InitTextCanvas(&txn, &canvas, func_ov039_020bc994(), 0, 0);
    info = screen->slots[entry].info;
    name = info->name;
    width = G2D_MeasureTextWidth_02016bc0(txn.pFont, txn.hSpace, name);
    if (info->type == 4) {
        limit = 0x4f;
    } else {
        limit = 0x62;
    }
    if (width >= limit) {
        txn.pFont = func_ov039_020bc9ac();
    }
    DrawText(&txn, 3, 4, color, name);
    tile = slot * 0x1a + 0x1c8;
    func_0200344c(screen->labelTiles, 0x680);
    GX_LoadBG2Char_02007a90(screen->labelTiles, tile * 0x40, 0x680);
    column = (slot == 1) + 13;
    FillBackgroundTileRectangle_02017adc(G2_GetBG2ScrPtr_02006e88(), 13, 2, column, slot * 2 + 5 + (slot >= 2 ? 3 : 0), 0x20, tile, 0);
}
