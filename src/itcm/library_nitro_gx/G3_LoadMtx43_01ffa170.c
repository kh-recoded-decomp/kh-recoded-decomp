#include "nitro/fx.h"

extern void GX_SendFifo48B(const void *src, void *dst);

void G3_LoadMtx43_01ffa170(const MtxFx43 *m) {
    *(volatile unsigned int *)0x4000400 = 0x17;
    GX_SendFifo48B(m, (void *)0x4000400);
}
