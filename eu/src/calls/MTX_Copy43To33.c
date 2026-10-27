#pragma anon_unions

#include "nitro/fx.h"

/* These caller-clobbered bindings apply only to this leaf's file. */
register const MtxFx43 *sMatrixSource __asm("r0");
register fx32 *sMatrixDestination __asm("r1");

void MTX_Copy43To33(const MtxFx43 *source, MtxFx33 *destination)
{
    sMatrixSource = source;
    sMatrixDestination = destination->a;

    /* Snapshot the rotation before writing, so the buffers may overlap. */
    fx32 m00 = sMatrixSource->_00;
    fx32 m01 = sMatrixSource->_01;
    fx32 m02 = sMatrixSource->_02;
    fx32 m10 = sMatrixSource->_10;
    fx32 m11 = sMatrixSource->_11;
    fx32 m12 = sMatrixSource->_12;
    fx32 m20 = sMatrixSource->_20;
    fx32 m21 = sMatrixSource->_21;
    fx32 m22 = sMatrixSource->_22;

    /* Copy the transposed rotation block, one output row at a time. */
    sMatrixDestination[0] = m00;
    sMatrixDestination[1] = m10;
    sMatrixDestination[2] = m20;
    sMatrixDestination += 3;
    sMatrixDestination[0] = m01;
    sMatrixDestination[1] = m11;
    sMatrixDestination[2] = m21;
    sMatrixDestination += 3;
    sMatrixDestination[0] = m02;
    sMatrixDestination[1] = m12;
    sMatrixDestination[2] = m22;
    sMatrixDestination += 3;
}
