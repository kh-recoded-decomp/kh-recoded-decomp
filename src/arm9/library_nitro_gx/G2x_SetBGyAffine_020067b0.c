#include "nitro/fx.h"

void G2x_SetBGyAffine_020067b0(u32 regAddr, const MtxFx22 *mtx, int centerX, int centerY,
                               int x, int y)
{
    fx32 dx, dy, refX, refY;

    *((vu32 *)regAddr + 0) = (u32)((u16)(s16)(mtx->_00 >> 4) | (u16)(s16)(mtx->_01 >> 4) << 16);
    *((vu32 *)regAddr + 1) = (u32)((u16)(s16)(mtx->_10 >> 4) | (u16)(s16)(mtx->_11 >> 4) << 16);
    dx = x - centerX;
    dy = y - centerY;
    refX = mtx->_00 * dx + mtx->_01 * dy + (centerX << 12);
    refY = mtx->_10 * dx + mtx->_11 * dy + (centerY << 12);
    *((vu32 *)regAddr + 2) = (u32)(refX >> 4);
    *((vu32 *)regAddr + 3) = (u32)(refY >> 4);
}
