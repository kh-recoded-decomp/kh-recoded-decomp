#include "nitro/types.h"

typedef void (*LayerLoadFunc)(const void *src, u32 offset, u32 size);

typedef struct {
    int ids[4];
} LayerIdSet4;

typedef struct {
    LayerLoadFunc loaders[4];
} LayerLoaderSet4;

extern const LayerIdSet4 data_ov039_020be740;
extern const LayerLoaderSet4 data_ov039_020be7ec;
extern int data_ov039_020bea00;
extern void PXI_Init_020b9d48(int layers, int id);
extern int UpdateWidgetLayerDefault_020b9df0(int layers, int id);

void LoadBgLayerSet4_020bac24(void)
{
    LayerIdSet4 idSet = data_ov039_020be740;
    LayerLoaderSet4 loaderSet = data_ov039_020be7ec;
    u32 i;

    for (i = 0; i < 4; i++) {
        int id = idSet.ids[i];
        int base;
        int layer;

        PXI_Init_020b9d48(data_ov039_020bea00 + 0xc9a0, id);
        base = data_ov039_020bea00;
        layer = UpdateWidgetLayerDefault_020b9df0(base + 0xc9a0, id);
        loaderSet.loaders[i]((const void *)layer, 0, *(u16 *)(base + 0xc9ac) << 1);
    }
}
