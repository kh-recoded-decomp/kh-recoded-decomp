#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x450];
    void *layerScreens[3];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;
extern int UpdateWidgetLayerDefault_020b9df0(FieldManager *manager, int layer);

void RefreshFieldLayerIfUnbound_020736d0(int layer)
{
    void *screen = NULL;

    switch (layer) {
    case 9:
        screen = data_ov001_020a04a4.manager->layerScreens[0];
        break;
    case 10:
        screen = data_ov001_020a04a4.manager->layerScreens[1];
        break;
    case 11:
        screen = data_ov001_020a04a4.manager->layerScreens[2];
        break;
    }
    if (screen == NULL) {
        UpdateWidgetLayerDefault_020b9df0(data_ov001_020a04a4.manager, layer);
    }
}
