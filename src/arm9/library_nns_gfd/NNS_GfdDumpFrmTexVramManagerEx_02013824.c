#include "nitro/types.h"
#include "nnsys/gfd.h"

extern NNSGfdFrmTexRegionState data_02055c78[NNS_GFD_NUM_TEX_VRAM_REGION];

void NNS_GfdDumpFrmTexVramManagerEx_02013824(NNSGfdFrmTexVramDebugDumpCallBack callback, void *userContext)
{
    int i;

    for (i = 0; i < NNS_GFD_NUM_TEX_VRAM_REGION; i++) {
        const NNSGfdFrmTexRegionState *region = &data_02055c78[i];
        callback(i, region->head + region->baseAddress, region->tail + region->baseAddress,
                 region->bHalfSize ? 0x10000 : 0x20000, region->bActive, userContext);
    }
}
