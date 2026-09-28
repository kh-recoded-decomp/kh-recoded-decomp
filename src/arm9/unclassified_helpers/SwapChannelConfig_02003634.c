#include "nitro/types.h"

extern u32 func_02002ed8(void);
extern u32 func_020036a4(int index);
extern u32 func_02003784(int index);
extern void func_02003828(int index, u32 value);
extern void func_0200383c(int index, u32 value);
extern void func_02003c80(int a, u32 b, int c);

void SwapChannelConfig_02003634(void) {
    u32 value;

    func_02002ed8();
    value = func_020036a4(2);
    func_02003828(2, value);
    value = func_02003784(2);
    func_0200383c(2, value);
    func_02003c80(1, 0x2000000, 0x2a);
}
