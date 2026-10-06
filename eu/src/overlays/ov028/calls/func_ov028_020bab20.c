#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern u32 func_ov001_0206e644(void);
extern u32 func_ov001_02067f9c(void);
extern u32 func_ov001_02067f8c(u32 value);
extern void func_ov001_02063848(u32 param1, u32 param2);

u32 func_ov028_020bab20(void)
{
    u32 context = data_ov028_020bb3a0;
    u32 arg1;
    u32 arg2;

    arg1 = func_ov001_0206e644();
    arg2 = func_ov001_02067f9c();
    arg1 = func_ov001_02067f8c(arg1);
    func_ov001_02063848(arg2, arg1);
    *(u16 *)(context + 6) = *(u16 *)(context + 6) | 2;
    return 7;
}
