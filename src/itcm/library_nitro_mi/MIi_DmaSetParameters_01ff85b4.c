#include "nitro/types.h"

extern int OS_DisableInterrupts_02004938(void);
extern int OS_RestoreInterrupts_0200494c(int enabled);

void MIi_DmaSetParameters_01ff85b4(u32 dmaNo, u32 src, u32 dest, u32 ctrl, u32 mode) {
    int enabled;
    vu32 *regs;
    u32 dummy;

    if (!(mode & 1)) {
        enabled = OS_DisableInterrupts_02004938();
    }
    regs = (vu32 *)(0x040000b0 + dmaNo * 12);
    if (mode & 0x10) {
        vu32 *fill = (vu32 *)(0x040000e0 + dmaNo * 4);
        *fill = src;
        src = (u32)fill;
    } else if (mode & 0x20) {
        vu16 *fill = (vu16 *)(0x040000e0 + dmaNo * 4);
        *fill = (u16)src;
        src = (u32)fill;
    }
    regs[0] = src;
    regs[1] = dest;
    regs[2] = ctrl;
    if (mode & 2) {
        dummy = *(vu32 *)0x040000b0;
        dummy = *(vu32 *)0x040000b0;
        if (!(mode & 4) && dmaNo == 0) {
            regs[0] = 0;
            regs[1] = 0;
            regs[2] = 0x81400001;
        }
    }
    if (!(mode & 1)) {
        OS_RestoreInterrupts_0200494c(enabled);
    }
    if (mode & 2) {
        dummy = *(vu32 *)0x040000b0;
        dummy = *(vu32 *)0x040000b0;
    }
}
