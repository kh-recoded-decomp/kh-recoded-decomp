#include "nitro/fx.h"

extern void MI_Copy36B(const void *src, void *dst);

void G3_MultMtx33_01ffa1a8(const MtxFx33 *m) {
    *(volatile unsigned int *)0x4000400 = 0x1a;
    MI_Copy36B(m, (void *)0x4000400);
}
