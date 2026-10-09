#include "libs/nitro/gx/gx_internal.h"

#pragma explicit_zero_data on

GXDataState gGXDataState = {
    1,
    0,
};

/* NitroSDK uses DMA channel 3 for graphics transfers by default. */
u32 GXi_DmaId = 3;
