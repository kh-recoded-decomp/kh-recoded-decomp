#include "nitro/types.h"

extern unsigned FX_GetSqrtResult_01ff9db8(void);

int FX_Sqrt_01ff9cfc(int value) {
    if (value <= 0) {
        return 0;
    }
    *(volatile u16 *)0x040002b0 = 1;
    *(volatile u64 *)0x040002b8 = (u64)value << 32;
    return FX_GetSqrtResult_01ff9db8();
}
