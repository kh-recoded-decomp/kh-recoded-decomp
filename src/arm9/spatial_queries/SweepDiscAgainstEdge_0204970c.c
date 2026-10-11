#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionDisc {
    VecFx32 center;
    fx32 radius;
    VecFx32 normal;
} CollisionDisc;

typedef struct CollisionEdge {
    VecFx32 vertex;
    VecFx32 direction;
} CollisionEdge;

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern int FixedPointMultiply12(int left, int right);
extern fx32 func_02047dac(fx32 value);
extern VecFx32 NormalizeVectorOut_0204840c(const VecFx32 *src);
extern VecFx32 func_02048b30(const VecFx32 *v, s32 scale);
extern VecFx32 MultAddOut_02048c48(fx32 scale, const VecFx32 *v, const VecFx32 *add);
extern VecFx32 RemoveNormalComponent_02049898(const VecFx32 *vec, const VecFx32 *normal, fx32 *outDot);
extern Vec2Fx32 SetFx32Pair_020498f8(fx32 a, fx32 b);
extern int Min_02049910(int a, int b);
extern void SwapAndNegateSecond_0204991c(fx32 *first, fx32 *second);
extern Vec2Fx32 AddFx32Pair_02049950(const Vec2Fx32 *a, const Vec2Fx32 *b);
extern Vec2Fx32 ScaleFx32Pair_02049984(const Vec2Fx32 *pair, fx32 scale);
extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);
extern fx32 DotFx32Xy_0204a390(const Vec2Fx32 *a, const Vec2Fx32 *b);
extern fx32 NormalizeXy_0204a3e4(Vec2Fx32 *xy);

void SweepDiscAgainstEdge_0204970c(const VecFx32 *offset, CollisionDisc *disc, const CollisionEdge *edge, const VecFx32 *binormal, const VecFx32 *normal, const VecFx32 *velocity, fx32 distance, s8 sign, VecFx32 *out)
{
    VecFx32 perp;
    VecFx32 axis;
    VecFx32 rejected;
    VecFx32 normalized;
    VecFx32 scaled;
    VecFx32 blended;
    VecFx32 axisCopy;
    VecFx32 chosen;
    fx32 dot;
    Vec2Fx32 planar;
    Vec2Fx32 rim;
    Vec2Fx32 side;
    Vec2Fx32 dir;
    Vec2Fx32 pair;
    Vec2Fx32 sum;
    Vec2Fx32 alongPlanar;
    Vec2Fx32 alongSide;
    fx32 length;
    fx32 shrink;
    fx32 clamped;
    s32 facing;
    fx32 facingDot;

    rejected = RemoveNormalComponent_02049898(&disc->normal, &edge->direction, &dot);
    perp = rejected;
    if (dot < 0xff0) {
        normalized = NormalizeVectorOut_0204840c(&perp);
        chosen = normalized;
    } else {
        chosen = *binormal;
    }
    axisCopy = chosen;
    axis = axisCopy;
    pair = SetFx32Pair_020498f8(VEC_DotProduct_01ff9e6c(binormal, &axis), VEC_DotProduct_01ff9e6c(normal, &axis));
    planar = pair;
    length = func_02047dac(dot);
    if (length > 0x10) {
        shrink = FixedPointMultiply12(func_02047dac(planar.x), FX_Div_01ff9c84(0x1000, length) - 0x1000);
    } else {
        shrink = 0;
    }
    shrink = FixedPointMultiply12(distance, shrink);
    clamped = Min_02049910(distance + shrink, disc->radius);
    rim.x = FX_Div_01ff9c84(sign * clamped, disc->radius);
    rim.y = ComputeOneMinusSquareFraction_02049d6c(rim.x);
    side = planar;
    SwapAndNegateSecond_0204991c(&side.x, &side.y);
    alongPlanar = ScaleFx32Pair_02049984(&planar, DotFx32Xy_0204a390(&rim, &planar));
    alongSide = ScaleFx32Pair_02049984(&side, FixedPointMultiply12(DotFx32Xy_0204a390(&rim, &side), length));
    sum = AddFx32Pair_02049950(&alongPlanar, &alongSide);
    dir = sum;
    NormalizeXy_0204a3e4(&dir);
    facingDot = VEC_DotProduct_01ff9e6c(normal, offset);
    facing = -1;
    if (facingDot < 0) {
        facing = 1;
    }
    scaled = func_02048b30(binormal, dir.x * facing);
    *out = scaled;
    blended = MultAddOut_02048c48(dir.y, normal, out);
    *out = blended;
    VEC_Normalize_01ff9f88(out, out);
}
