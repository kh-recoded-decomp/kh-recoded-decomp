#include "nitro/types.h"

extern void SwapInts_0204993c(int *first, int *second);

void SwapAndNegateSecond_0204991c(int *first, int *second)
{
    SwapInts_0204993c(first, second);
    *second *= -1;
}
