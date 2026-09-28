#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void FX_InvAsync_01ff9d88(fx32 x);
extern fx64c func_01ff9d30(void);
extern fx64c func_02023ba4(fx64c numerator, fx64c denominator);

typedef struct {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

static inline void CP_SetDivImm64_64(u64 numerator, u64 denominator)
{
    *(volatile u64 *)0x04000290 = numerator;
    *(volatile u64 *)0x04000298 = denominator;
}

static inline void FX_InvAsyncImm(fx32 denominator)
{
    CP_SetDivImm64_64((u64)0x1000 << 32, (u64)(u32)denominator);
}

static inline fx32 FX_Mul32x64c(fx32 factor, fx64c wideValue)
{
    fx64c product = wideValue * factor + 0x80000000LL;
    return (fx32)(product >> 32);
}

void MTX_OrthoW_02005f10(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far,
                         fx32 scaleW, MtxFx44 *mtx)
{
    fx64c recipWidth, recipHeight, recipDepth;

    FX_InvAsync_01ff9d88(right - left);

    mtx->_01 = 0;
    mtx->_02 = 0;
    mtx->_03 = 0;
    mtx->_10 = 0;
    mtx->_12 = 0;
    mtx->_13 = 0;
    mtx->_20 = 0;
    mtx->_21 = 0;
    mtx->_23 = 0;
    mtx->_33 = scaleW;

    recipWidth = func_01ff9d30();
    FX_InvAsyncImm(top - bottom);
    if (scaleW != 0x1000)
        recipWidth = func_02023ba4(recipWidth * scaleW, 0x1000);
    mtx->_00 = FX_Mul32x64c(0x1000 * 2, recipWidth);

    recipHeight = func_01ff9d30();
    FX_InvAsyncImm(near - far);
    if (scaleW != 0x1000)
        recipHeight = func_02023ba4(recipHeight * scaleW, 0x1000);
    mtx->_11 = FX_Mul32x64c(0x1000 * 2, recipHeight);

    recipDepth = func_01ff9d30();
    if (scaleW != 0x1000)
        recipDepth = func_02023ba4(recipDepth * scaleW, 0x1000);
    mtx->_22 = FX_Mul32x64c(0x1000 * 2, recipDepth);

    mtx->_30 = FX_Mul32x64c(-(right + left), recipWidth);
    mtx->_31 = FX_Mul32x64c(-(top + bottom), recipHeight);
    mtx->_32 = FX_Mul32x64c(far + near, recipDepth);
}
