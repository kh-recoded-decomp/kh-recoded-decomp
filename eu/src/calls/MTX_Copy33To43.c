#include "nitro/fx_types.h"

/* These caller-clobbered bindings apply only to this leaf's file. */
register const fx32 *sSourceCoefficients __asm("r0");
register fx32 *sDestinationCoefficients __asm("r1");

static __forceinline void CopyMatrixRow(void)
{
    fx32 first = sSourceCoefficients[0];
    fx32 second = sSourceCoefficients[1];
    fx32 third = sSourceCoefficients[2];
    sSourceCoefficients += 3;

    sDestinationCoefficients[0] = first;
    sDestinationCoefficients[1] = second;
    sDestinationCoefficients[2] = third;
    sDestinationCoefficients += 3;
}

void MTX_Copy33To43(const void *source, void *destination)
{
    sSourceCoefficients = source;
    sDestinationCoefficients = destination;

    CopyMatrixRow();
    CopyMatrixRow();
    CopyMatrixRow();

    /* A 3x3 rotation has no translation in the fourth row. */
    fx32 zero = 0;
    sDestinationCoefficients[0] = zero;
    sDestinationCoefficients[1] = zero;
    sDestinationCoefficients[2] = zero;
}
