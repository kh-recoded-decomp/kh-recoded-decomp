#include "nitro/types.h"
#include "nitro/fx_types.h"

extern double MSL_Sqrt(double x);
extern float NthRootFloat(float value, int n);
extern u16 Math_AcosIdx(fx32 x);
extern const s16 gSinFx12Table[4096];

static inline fx32 FloatToFx32(float value)
{
    return (fx32)(value > 0 ? 4096.0f * value + 0.5f : 4096.0f * value - 0.5f);
}

static inline fx32 CosIdx(int index)
{
    return gSinFx12Table[(0x400 - (index >> 4)) & 0xfff];
}

/* A third of a turn as the game writes it (0x5555 would be exact), kept 64-bit. */
#define THIRD_TURN 0x5553LL

static inline fx32 MulFx32(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

/* Real roots of x^3 + quadratic*x^2 + linear*x + constant (Cardano, or the trigonometric form when
 * all three roots are real); a missing root is 0x7fffffff. */
void SolveMonicCubic(s64 quadratic, s64 linear, s64 constant, fx32 *roots)
{
    float a = quadratic / 4096.0f;
    float b = linear / 4096.0f;
    float c = constant / 4096.0f;
    float aSquared = a * a;
    float p = aSquared / -3.0f + b;
    float q = c + (2.0f * (aSquared * a) / 27.0f - a * b / 3.0f);
    float p3 = p / 3.0f;
    float q2 = q / 2.0f;
    float p3Cubed = p3 * (p3 * p3);
    fx32 shift = quadratic / 3;
    float discriminant = p3Cubed + q2 * q2;
    float delta = -108.0f * discriminant;

    if (delta <= 0.0f) {
        float root = (float)MSL_Sqrt(discriminant);
        fx32 u = FloatToFx32(NthRootFloat(0.0f - q2 + root, 3));

        if (delta < 0.0f) {
            fx32 v = FloatToFx32(NthRootFloat(0.0f - q2 - root, 3));

            roots[0] = u + v - shift;
            roots[2] = 0x7fffffff;
            roots[1] = 0x7fffffff;
        } else {
            roots[0] = u * 2 - shift;
            roots[1] = -(u + shift);
            roots[2] = -(u + shift);
        }
    } else {
        fx32 radius = FloatToFx32((float)MSL_Sqrt((0.0f - p) / 3.0f));
        fx32 cosine = FloatToFx32((float)((double)(0.0f - q2) / MSL_Sqrt(0.0f - p3Cubed)));
        u16 angle;
        fx32 scale;

        if (cosine > 0x1000) {
            cosine = 0x1000;
        } else if (cosine < -0x1000) {
            cosine = -0x1000;
        }
        angle = Math_AcosIdx(cosine) / 3;
        scale = FloatToFx32((float)(2.0 * MSL_Sqrt(0.0f - p3)));
        roots[0] = MulFx32(radius * 2, CosIdx(angle)) - shift;
        roots[1] = MulFx32(scale, CosIdx((angle + THIRD_TURN) & 0xffff)) - shift;
        roots[2] = MulFx32(scale, CosIdx((angle - THIRD_TURN) & 0xffff)) - shift;
    }
}
