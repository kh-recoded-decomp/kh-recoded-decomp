#include "nitro/types.h"

extern int data_020be920;
extern void *PXI_Init_0202a638(int handle);

/* Releases the MobiClip source handle and invalidates it */
void MobiClip_SrcClose_020bde6c(void) {
    PXI_Init_0202a638(data_020be920);
    data_020be920 = -1;
}
