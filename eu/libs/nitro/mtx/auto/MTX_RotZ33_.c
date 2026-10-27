#pragma anon_unions

#include "nitro/fx.h"

/* Keep the original packed-store cursor and zero in caller-clobbered registers. */
register fx32 *sMatrixCursor __asm("r0");
register fx32 sMatrixZero __asm("r3");

void MTX_RotZ33_(MtxFx33 *matrix, fx32 sine, fx32 cosine)
{
    /* First row: cosine, sine, zero. */
    sMatrixCursor = matrix->a;
    *sMatrixCursor++ = cosine;
    sMatrixZero = 0;
    sMatrixCursor[0] = sine;
    sMatrixCursor[1] = sMatrixZero;
    sMatrixCursor += 2;

    /* Begin the second row with negative sine and cosine. */
    sine = (fx32)(0u - (u32)sine);
    sMatrixCursor[0] = sine;
    sMatrixCursor[1] = cosine;
    sMatrixCursor += 2;

    /* Finish the second row, then write the unchanged Z-axis basis. */
    volatile fx32 *remainingCoefficients = sMatrixCursor;
    fx32 unit = FX32_ONE;
    remainingCoefficients[0] = sMatrixZero;
    remainingCoefficients[1] = sMatrixZero;
    remainingCoefficients[2] = sMatrixZero;
    remainingCoefficients[3] = unit;
}
