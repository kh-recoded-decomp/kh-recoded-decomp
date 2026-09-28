#include "nitro/types.h"

extern u32 data_020569cc;
extern void func_01ff8830(void *dst, int value, int size);
extern void OS_SetIrqFunction(u32 intrBits, void *function);
extern u32 OS_EnableIrqMask(u32 mask);
extern int GX_VBlankIntr(int enable);

void InitVBlankInterrupt_020010cc(void) {
    func_01ff8830(&data_020569cc, 0, 0x114);
    OS_SetIrqFunction(1, (void *)0x1ff8000);
    OS_EnableIrqMask(1);
    GX_VBlankIntr(1);
}
