#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags_b0 : 4;
    u8 hasTextLayer : 1;
    u8 flags_b5 : 3;
    u8 pad_11[0xb0 - 0x11];
    u8 textLayer[4];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void DestroyFndObjectList_020014f0(void *list);
extern void InitTextLayerDefault_02001494(void *list, int mode, void *font, const u16 *layout);

void CreatePanelTextLayer_020625a0(void *font)
{
    u16 layout[8];

    if (g_panelState_0206c460->hasTextLayer) {
        DestroyFndObjectList_020014f0(g_panelState_0206c460->textLayer);
    }
    layout[0] = 1;
    layout[1] = 0;
    layout[2] = 0x1f;
    layout[3] = 0xf;
    layout[4] = 1;
    layout[5] = 0xf;
    layout[6] = 0;
    layout[7] = 3;
    InitTextLayerDefault_02001494(g_panelState_0206c460->textLayer, 7, font, layout);
    g_panelState_0206c460->hasTextLayer = 1;
}
