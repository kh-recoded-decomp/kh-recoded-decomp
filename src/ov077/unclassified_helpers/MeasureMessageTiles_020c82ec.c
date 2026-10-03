#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef union {
    struct {
        s16 width;
        s16 height;
    };
    u32 packed;
} TileSize;

typedef struct {
    u8 pad_000[0x608];
    u8 charBase[1];
} MessageWindow;

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *canvas, void *charBase, int areaWidth,
                                                int areaHeight, int colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern NNSG2dTextRect func_ov077_020c826c(const NNSG2dTextCanvas *txn, const u16 *text);

TileSize MeasureMessageTiles_020c82ec(MessageWindow *window, int style, const u16 *text)
{
    NNSG2dCharCanvas canvas;
    NNSG2dTextCanvas txn;
    NNSG2dTextRect rect;
    TileSize size;

    G2D_InitializeLinearCanvas_02017a2c(&canvas, window->charBase, 0x1c, 0x14, 8);
    txn.pFont = func_ov039_020bc994();
    txn.pCanvas = &canvas;
    txn.hSpace = 0;
    txn.vSpace = 1;
    rect = func_ov077_020c826c(&txn, text);
    size.width = (rect.width >> 3) + (u16)((rect.width & 7) ? 1 : 0);
    size.height = (rect.height >> 3) + (u16)((rect.height & 7) ? 1 : 0);
    if (style == 2) {
        size.height += 2;
        size.width = (size.width < 0x1a) ? 0x1a : size.width;
    }
    if (size.width == 0) {
        size.width = 1;
    }
    if (size.height == 0) {
        size.height = 1;
    }
    size.width += 2;
    size.height += 2;
    size.width += size.width & 1;
    if (size.width > 0x20) {
        size.width = 0x20;
    }
    return size;
}

