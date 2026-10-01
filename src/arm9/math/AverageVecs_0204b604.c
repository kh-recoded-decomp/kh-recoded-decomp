#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))
#define va_arg(ap, type) (*(type *)(((ap) += 4) - 4))
#define va_end(ap) ((void)0)

extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void DivideVecFx32ByScalar_0204a700(VecFx32 *vec, int divisor);

VecFx32 AverageVecs_0204b604(int count, ...)
{
    int i;
    VecFx32 sum;
    VecFx32 next;
    va_list args;
    int total;

    va_start(args, count);
    total = count;
    sum = *va_arg(args, VecFx32 *);
    for (i = 1; i < total; i++) {
        VEC_Add_01ff9e0c(&sum, va_arg(args, VecFx32 *), &next);
        sum = next;
    }
    if (total == 2) {
        sum.x >>= 1;
        sum.y >>= 1;
        sum.z >>= 1;
    } else {
        DivideVecFx32ByScalar_0204a700(&sum, total);
    }
    va_end(args);
    return sum;
}
