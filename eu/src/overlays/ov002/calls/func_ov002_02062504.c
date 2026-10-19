#include "src/overlays/ov002/Ov002PanelState.h"

extern BOOL DestroyFndObjectList(void *entry);
extern BOOL InitTextLayerDefault(void *entry, int mode,
                                 NNSG2dFont *font, const u16 *data);

void func_ov002_02062504(NNSG2dFont *font) {
    u16 data[8];

    if (data_ov002_0206c460->mainBg2TextInitialized) {
        DestroyFndObjectList(&data_ov002_0206c460->textLayers[1]);
    }

    data[0] = 0;
    data[1] = 0;
    data[2] = 0x20;
    data[3] = 0x18;
    data[4] = 1;
    data[5] = 0xf;
    data[6] = 0;
    data[7] = 3;

    InitTextLayerDefault(&data_ov002_0206c460->textLayers[1], 2, font, data);
    data_ov002_0206c460->mainBg2TextInitialized = 1;
}
