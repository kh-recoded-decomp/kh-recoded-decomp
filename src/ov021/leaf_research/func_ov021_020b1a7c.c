#include "nitro/types.h"

typedef void code();

extern u32 data_020b56a4;
extern u32 func_ov001_0209c18c();
extern u32 func_ov001_0209c3c0();
extern u32 func_ov001_0209c3cc();

u32 func_ov021_020b1a7c(int self)
{
    s32 member;
    u32 arg;
    s32 state;

    member = func_ov001_0209c18c(*(u16 *)(data_020b56a4 + 0x16));
    if (member != 0) {
        arg = func_ov001_0209c3cc();
        state = func_ov001_0209c3c0();
        if (state != 0) {
            if (*(code **)(state + 0x18f54) != (code *)0x0) {
                (**(code **)(state + 0x18f54))(member, arg);
            }
        }
        state = func_ov001_0209c3c0();
        if ((state != 0) && (*(code **)(state + 0x18f58) != (code *)0x0)) {
            (**(code **)(state + 0x18f58))(member, self + 0x34);
        }
    }
    return 0;
}
