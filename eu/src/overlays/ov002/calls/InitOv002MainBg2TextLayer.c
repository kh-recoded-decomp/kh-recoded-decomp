#include "src/overlays/ov002/Ov002PanelState.h"

extern BOOL DestroyFndObjectList(void *entry);
extern BOOL InitTextLayerDefault(void *entry, int mode,
                                 NNSG2dFont *font, const u16 *data);

void InitOv002MainBg2TextLayer(NNSG2dFont *font) {
    u16 data[8];

    if (gOv002ProfilePanelWork->mainBg2TextInitialized) {
        DestroyFndObjectList(&gOv002ProfilePanelWork->textLayers[1]);
    }

    data[0] = 0;
    data[1] = 0;
    data[2] = 0x20;
    data[3] = 0x18;
    data[4] = 1;
    data[5] = 0xf;
    data[6] = 0;
    data[7] = 3;

    InitTextLayerDefault(&gOv002ProfilePanelWork->textLayers[1], 2, font, data);
    gOv002ProfilePanelWork->mainBg2TextInitialized = 1;
}
