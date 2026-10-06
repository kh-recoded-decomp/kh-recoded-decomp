#include "nitro/types.h"

typedef void code();

extern u32 data_ov021_020b56c4;
extern u32 GetStageMotionRecord();
extern u32 func_ov001_0209c3e8();
extern u32 GetGlobalScaleValue();

u32 func_ov021_020b1a9c(int self)
{
    s32 member;
    u32 arg;
    s32 state;

    member = GetStageMotionRecord(*(u16 *)(data_ov021_020b56c4 + 0x16));
    if (member != 0) {
        arg = GetGlobalScaleValue();
        state = func_ov001_0209c3e8();
        if (state != 0) {
            if (*(code **)(state + 0x18f54) != (code *)0x0) {
                (**(code **)(state + 0x18f54))(member, arg);
            }
        }
        state = func_ov001_0209c3e8();
        if ((state != 0) && (*(code **)(state + 0x18f58) != (code *)0x0)) {
            (**(code **)(state + 0x18f58))(member, self + 0x34);
        }
    }
    return 0;
}
