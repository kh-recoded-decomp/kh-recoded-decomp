#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Vec2Fx32 { fx32 x; fx32 y; } Vec2Fx32;

extern void func_0204a2e0(const Vec2Fx32 *a, const Vec2Fx32 *b, Vec2Fx32 *out);

void AddFx32Pair_02040b98(Vec2Fx32 *out, const Vec2Fx32 *a, const Vec2Fx32 *b)
{
    Vec2Fx32 tmp;
    func_0204a2e0(a, b, &tmp);
    *out = tmp;
}
