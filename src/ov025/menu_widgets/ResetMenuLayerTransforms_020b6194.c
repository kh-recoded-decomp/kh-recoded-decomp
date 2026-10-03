#include "nitro/types.h"

typedef void (*LayerScaleFunc)(int layer, int offset, int scale);

typedef struct LayerIdPair {
    int ids[2];
} LayerIdPair;

typedef struct LayerFuncPair {
    LayerScaleFunc funcs[2];
} LayerFuncPair;

extern u32 _data_ov025_020b7760;
extern LayerIdPair data_ov025_020b7680;
extern LayerFuncPair data_ov025_020b7720;
extern int UpdateWidgetLayerDefault_020b9df0(int owner, int layerId);

void ResetMenuLayerTransforms_020b6194(void)
{
    LayerIdPair layerIds = data_ov025_020b7680;
    LayerFuncPair applyFuncs = data_ov025_020b7720;
    u32 menu = _data_ov025_020b7760;
    u32 i;

    if (menu != 0 && *(int *)(menu + 0x64e4) != 0) {
        for (i = 0; i < 2; i++) {
            int layer = UpdateWidgetLayerDefault_020b9df0(menu + 0x64c8, layerIds.ids[i]);
            applyFuncs.funcs[i](layer, 0, 0x1000);
        }
    }
}
