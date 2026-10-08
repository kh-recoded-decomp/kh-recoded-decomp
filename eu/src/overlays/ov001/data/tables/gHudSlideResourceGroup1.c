#include "nitro/types.h"

extern u8 data_ov001_0209ec68[];
extern u32 gHudSlideResourceGroup1Descriptor[];
extern u8 data_ov001_0209ec70[];

void *gHudSlideResourceGroup1[3] = {
    data_ov001_0209ec68,
    gHudSlideResourceGroup1Descriptor,
    data_ov001_0209ec70,
};
