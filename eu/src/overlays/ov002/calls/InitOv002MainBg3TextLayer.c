#include "src/overlays/ov002/Ov002PanelState.h"

extern BOOL DestroyFndObjectList(void *entry);
extern BOOL InitTextLayerDefault(void *entry, int mode,
                                 NNSG2dFont *font, const u16 *data);

void InitOv002MainBg3TextLayer(NNSG2dFont *font) {
    u16 data[8];

    if (gOv002ProfilePanelWork->mainBg3TextInitialized) {
        DestroyFndObjectList(&gOv002ProfilePanelWork->textLayers[0]);
    }

    data[0] = 1;
    data[1] = 0;
    data[2] = 0x1f;
    data[3] = 0xf;
    data[4] = 1;
    data[5] = 0xf;
    data[6] = 0;
    data[7] = 3;

    InitTextLayerDefault(&gOv002ProfilePanelWork->textLayers[0], 3, font, data);
    gOv002ProfilePanelWork->mainBg3TextInitialized = 1;
}
