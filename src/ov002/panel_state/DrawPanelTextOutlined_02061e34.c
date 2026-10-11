#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct PanelTextLayer {
    u8 pad_00[0x10];
    NNSG2dTextCanvas txn;
    u8 pad_20[0x14];
} PanelTextLayer;

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 mainFlags;
    struct {
        u8 firstShown : 1;
        u8 rest : 7;
    } subFlags;
    u8 pad_12[0x36];
    PanelTextLayer layers[4];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern NNSG2dTextRect G2D_MeasureTextRectangle_02016c18(const NNSG2dFont *font, int hSpace, int vSpace, const void *text);
extern void DrawTextAnchored_020015a0(void *obj, int x, int y, int color, u32 flags, const u16 *text);

static inline NNSG2dTextRect GetCanvasTextRect(const NNSG2dTextCanvas *txn, const u16 *text)
{
    NNSG2dTextRect rect = G2D_MeasureTextRectangle_02016c18(txn->pFont, txn->hSpace, txn->vSpace, text);
    return rect;
}

void DrawPanelTextOutlined_02061e34(int screen, int which, int x, int y, int color, int shadowColor, int align, int shadowMode, const u16 *text)
{
    PanelTextLayer *layer;
    NNSG2dTextRect rect;

    if (text == NULL) {
        return;
    }
    if (screen == 0) {
        if (which == 0) {
            layer = &g_panelState_0206c460->layers[0];
            g_panelState_0206c460->mainFlags |= 0x40;
        } else {
            layer = &g_panelState_0206c460->layers[1];
            g_panelState_0206c460->mainFlags |= 0x80;
        }
    } else {
        if (which == 0) {
            layer = &g_panelState_0206c460->layers[2];
            g_panelState_0206c460->subFlags.firstShown = 1;
        } else {
            layer = &g_panelState_0206c460->layers[3];
            *(u8 *)&g_panelState_0206c460->subFlags |= 2;
        }
    }
    if (align != 0) {
        rect = GetCanvasTextRect(&layer->txn, text);
        x -= rect.width >> (align == 1);
    }
    if (shadowMode != 0) {
        if (shadowMode == 1) {
            DrawTextAnchored_020015a0(layer, x + 1, y + 1, shadowColor, 0, text);
        } else {
            DrawTextAnchored_020015a0(layer, x, y + 1, shadowColor, 0, text);
            DrawTextAnchored_020015a0(layer, x, y - 1, shadowColor, 0, text);
            DrawTextAnchored_020015a0(layer, x + 1, y, shadowColor, 0, text);
            DrawTextAnchored_020015a0(layer, x - 1, y, shadowColor, 0, text);
        }
    }
    DrawTextAnchored_020015a0(layer, x, y, color, 0, text);
}
