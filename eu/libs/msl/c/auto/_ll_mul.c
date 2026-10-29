#include "nitro/types.h"

u64 _ll_mul(u64 left, u64 right)
{
    register u32 linkRegister __asm("r14");
    register u32 resultLow __asm("r5");
    register u32 resultHigh __asm("r4");
    u64 lowProduct = (u64)(u32)left * (u32)right;

    /* A dead link write keeps lr saved. */
    linkRegister = 0;
    resultLow = (u32)lowProduct;
    resultHigh = (u32)(lowProduct >> 32);
    resultHigh += (u32)left * (u32)(right >> 32);
    resultHigh += (u32)right * (u32)(left >> 32);
    return ((u64)resultHigh << 32) | resultLow;
}
