#include "nitro/types.h"

typedef void (*LayerLoadFunc)(const void *src, u32 offset, u32 size);

typedef struct {
    int ids[3];
} LayerIdSet3;

typedef struct {
    LayerLoadFunc loaders[3];
} LayerLoaderSet3;

extern const LayerIdSet3 data_ov039_020be734;
extern const LayerLoaderSet3 data_ov039_020be7e0;
extern int data_ov039_020bea00;
extern void PXI_Init_020b9d48(int layers, int id);
extern int UpdateWidgetLayerDefault_020b9df0(int layers, int id);

void LoadBgLayerSet3_020bab8c(void)
{
    LayerIdSet3 idSet = data_ov039_020be734;
    LayerLoaderSet3 loaderSet = data_ov039_020be7e0;
    u32 i;

    for (i = 0; i < 3; i++) {
        int id = idSet.ids[i];
        int base;
        int layer;

        PXI_Init_020b9d48(data_ov039_020bea00 + 0xc9a0, id);
        base = data_ov039_020bea00;
        layer = UpdateWidgetLayerDefault_020b9df0(base + 0xc9a0, id);
        loaderSet.loaders[i]((const void *)layer, 0, *(u16 *)(base + 0xc9ac) << 1);
    }
}
