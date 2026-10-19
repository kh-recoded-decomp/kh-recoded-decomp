#include "src/overlays/ov002/Ov002PanelState.h"

extern BOOL DestroyFndObjectList(void *entry);
extern BOOL InitTextLayerDefault(void *entry, int mode,
                                 NNSG2dFont *font, const u16 *layout);

void CreatePanelTextLayer(NNSG2dFont *font)
{
    u16 layout[8];

    if (gOv002PanelState->subBg3TextInitialized) {
        DestroyFndObjectList(&gOv002PanelState->textLayers[2]);
    }
    layout[0] = 1;
    layout[1] = 0;
    layout[2] = 0x1f;
    layout[3] = 0xf;
    layout[4] = 1;
    layout[5] = 0xf;
    layout[6] = 0;
    layout[7] = 3;
    InitTextLayerDefault(&gOv002PanelState->textLayers[2], 7, font, layout);
    gOv002PanelState->subBg3TextInitialized = 1;
}
