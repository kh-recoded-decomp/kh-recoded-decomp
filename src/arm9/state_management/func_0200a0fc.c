#include "nitro/types.h"

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void func_0200a070(int a, int b, int c);
extern s32 data_02fffc00;

void func_0200a0fc(int value) {
    u32 state;
    volatile s32 current = data_02fffc00;

    if (value != current) {
        state = func_02004938();
        func_0200a070(0xe, 0x11, 0);
        func_0200494c(state);
    }
}
