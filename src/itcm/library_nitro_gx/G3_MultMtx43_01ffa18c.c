#include "nitro/fx.h"

extern void GX_SendFifo48B(const void *src, void *dst);

void G3_MultMtx43_01ffa18c(const MtxFx43 *m) {
    *(volatile unsigned int *)0x4000400 = 0x19;
    GX_SendFifo48B(m, (void *)0x4000400);
}
