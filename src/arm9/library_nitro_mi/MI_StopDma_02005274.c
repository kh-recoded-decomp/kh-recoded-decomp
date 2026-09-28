#include "nitro/types.h"

extern int func_02004938(void);
extern void func_0200494c(int state, u32 value);

void MI_StopDma_02005274(int channel)
{
    int state;
    u32 value;
    int offset;
    vu32 *cnt;
    vu32 *regs;

    state = func_02004938();
    offset = channel * 0xc;
    cnt = (vu32 *)(offset + 0x40000b8);
    *cnt = *cnt & 0xc5ffffff;
    *cnt = *cnt & 0x7fffffff;
    value = *cnt;
    value = *cnt;
    if (channel == 0) {
        regs = (vu32 *)(offset + 0x40000b0);
        regs[0] = 0;
        value = 0x81400001;
        regs[1] = 0;
        regs[2] = value;
    }
    func_0200494c(state, value);
}
