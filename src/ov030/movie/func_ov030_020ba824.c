#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern u32 func_ov001_0206e644(void);
extern s8 GetSignedByteAt1_02067f9c(void);
extern s8 GetSignedByteAt3_02067f8c(u32 arg);
extern void func_ov001_02063848(u32 a, u32 b);

u32 func_ov030_020ba824(void)
{
    u32 ctx;
    u32 valueA;
    u32 valueB;

    ctx = g_moviePlayerCtx_020bd000;
    valueA = func_ov001_0206e644();
    valueB = GetSignedByteAt1_02067f9c();
    valueA = GetSignedByteAt3_02067f8c(valueA);
    func_ov001_02063848(valueB, valueA);
    *(u16 *)(ctx + 6) = *(u16 *)(ctx + 6) | 2;
    return 7;
}
