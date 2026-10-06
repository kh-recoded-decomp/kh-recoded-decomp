#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern u32 func_ov001_0206e644(void);
extern s8 func_ov001_02067f9c(void);
extern s8 func_ov001_02067f8c(u32 arg);
extern void func_ov001_02063848(u32 a, u32 b);

u32 func_ov030_020ba844(void)
{
    u32 ctx;
    u32 valueA;
    u32 valueB;

    ctx = data_ov030_020bd020;
    valueA = func_ov001_0206e644();
    valueB = func_ov001_02067f9c();
    valueA = func_ov001_02067f8c(valueA);
    func_ov001_02063848(valueB, valueA);
    *(u16 *)(ctx + 6) = *(u16 *)(ctx + 6) | 2;
    return 7;
}
