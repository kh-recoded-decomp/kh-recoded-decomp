#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct PanelTextLayer {
    u8 pad_00[0x10];
    NNSG2dTextCanvas txn;
    u8 pad_20[0x14];
} PanelTextLayer;

typedef struct PanelState {
    u8 pad_00[0x48];
    PanelTextLayer layers[4];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern NNSG2dTextRect G2D_MeasureTextRectangle_02016c18(const NNSG2dFont *font, int hSpace, int vSpace, const void *text);

static inline NNSG2dTextRect GetCanvasTextRect(const NNSG2dTextCanvas *txn, const u16 *text)
{
    NNSG2dTextRect rect = G2D_MeasureTextRectangle_02016c18(txn->pFont, txn->hSpace, txn->vSpace, text);
    return rect;
}

NNSG2dTextRect MeasurePanelTextSecondary_02062890(int which, const u16 *text)
{
    switch (which) {
    case 0:
        return GetCanvasTextRect(&g_panelState_0206c460->layers[2].txn, text);
    case 1:
        return GetCanvasTextRect(&g_panelState_0206c460->layers[3].txn, text);
    }
}
