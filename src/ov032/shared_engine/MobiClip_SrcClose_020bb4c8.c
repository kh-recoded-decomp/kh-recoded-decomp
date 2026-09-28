#include "nitro/types.h"

extern u32 data_ov032_020bffc0;
extern void PXI_Init_0202a638(u32 handle);

/* Releases the MobiClip source handle and invalidates it */
void MobiClip_SrcClose_020bb4c8(void) {
    PXI_Init_0202a638(data_ov032_020bffc0);
    data_ov032_020bffc0 = 0xffffffff;
}
