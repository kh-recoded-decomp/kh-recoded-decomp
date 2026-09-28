#include "nitro/types.h"

extern void GFXi_EnqueueCommand_02014090(u32 a, u32 b, u32 c, u32 d);
extern void DC_FlushRange_0200344c(const void *addr, u32 size);
extern void func_020072b4(void *addr, u32 arg1, u32 size);

void DispatchDrawCommand_020b75b0(u32 entity, int mode) {
    if (mode != 0) {
        DC_FlushRange_0200344c((void *)(entity + 0x10), 0x60);
        func_020072b4((void *)(entity + 0x10), 0xa0, 0x60);
        return;
    }
    GFXi_EnqueueCommand_02014090(0x1f, 0xa0, entity + 0x10, 0x60);
}
