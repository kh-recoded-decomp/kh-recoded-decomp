#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b);
extern s64 LongDiv_02023ba4(s64 numerator, s64 denominator);
extern void func_0204b0ac(VecFx32 *vec, const VecFx32 *axis, fx32 angle);

static inline VecFx32 Rotated(VecFx32 vec, const VecFx32 *axis, fx32 angle)
{
    func_0204b0ac(&vec, axis, angle);
    return vec;
}

static inline s32 AngleBetweenDirections(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 rawB;
    VecFx32 rawA;
    VecFx32 bDir;
    VecFx32 aDir;

    VEC_Normalize_01ff9f88(b, &rawB);
    bDir = rawB;
    VEC_Normalize_01ff9f88(a, &rawA);
    aDir = rawA;
    return AngleBetweenVecs_0204b070(&aDir, &bDir);
}

static inline fx32 AngleToRadians(s32 angle)
{
    return (fx32)LongDiv_02023ba4((s64)angle * 0x6488, 0x10000);
}

void RotateTowardVector_0204b404(const VecFx32 *from, const VecFx32 *to, fx32 ratio, VecFx32 *out)
{
    fx32 radians = AngleToRadians(AngleBetweenDirections(from, to));
    VecFx32 rotated = Rotated(*from, to, (fx32)(((fx64)radians * ratio + 0x800) >> 12));

    *out = rotated;
}
