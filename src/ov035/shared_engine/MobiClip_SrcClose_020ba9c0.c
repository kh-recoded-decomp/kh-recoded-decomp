#include "nitro/types.h"

extern u32 data_ov035_020bc460;
extern void *PXI_Init_0202a638(u32 handle);

void MobiClip_SrcClose_020ba9c0(void) {
    PXI_Init_0202a638(data_ov035_020bc460);
    data_ov035_020bc460 = 0xffffffff;
}
