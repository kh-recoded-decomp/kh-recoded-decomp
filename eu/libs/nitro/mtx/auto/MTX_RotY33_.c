#pragma anon_unions

#include "nitro/fx.h"

/* The zero and unit coefficients share the caller-clobbered r3 in this leaf. */
register fx32 sMatrixBasis __asm("r3");

void MTX_RotY33_(MtxFx33 *matrix, fx32 sine, fx32 cosine)
{
    /* Keep the SDK initializer's field writes in order. */
    volatile MtxFx33 *output = matrix;
    output->_00 = cosine;
    output->_22 = cosine;

    sMatrixBasis = 0;
    output->_01 = sMatrixBasis;
    output->_10 = sMatrixBasis;
    output->_12 = sMatrixBasis;
    output->_21 = sMatrixBasis;

    fx32 negativeSine = (fx32)(0u - (u32)sine);
    sMatrixBasis = FX32_ONE;
    output->_20 = sine;
    output->_02 = negativeSine;
    output->_11 = sMatrixBasis;
}
