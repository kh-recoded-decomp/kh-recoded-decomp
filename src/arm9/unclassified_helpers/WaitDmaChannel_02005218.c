#include "nitro/types.h"

extern int func_02004938(void);
extern void func_0200494c(int state);

void WaitDmaChannel_02005218(int channel)
{
    int state = func_02004938();
    volatile u32 *ctrl = (volatile u32 *)(0x04000000 + channel * 12 + 0xb8);

    while ((*ctrl & 0x80000000) != 0) {
    }

    if (channel == 0) {
        volatile u32 *reg = (volatile u32 *)(0x04000000 + channel * 12 + 0xb0);
        reg[0] = 0;
        reg[1] = 0;
        reg[2] = 0x81400001;
    }

    func_0200494c(state);
}
