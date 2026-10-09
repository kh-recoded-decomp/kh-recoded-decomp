#include "nitro/types.h"
#include "nitro/fx_types.h"

fx32 FX_Sqrt_01ff9cfc(fx32 value);
void SolveMonicQuadratic_0204c17c(fx32 linear, fx32 constant, fx32 *rootHigh, fx32 *rootLow);
void func_0204c200(s64 quadratic, s64 linear, s64 constant, fx32 *roots);

void SolveQuartic_0204c6c0(fx32 cubic, fx32 quadratic, fx32 linear, s64 constant, fx32 *roots)
{
    fx32 cubicSq = (fx32)(((s64)cubic * cubic) >> 12);
    fx32 depQuadratic = quadratic + -cubicSq * 3 / 8;
    s64 depLinear = linear + ((((s64)cubicSq * cubic) >> 12) / 8 - (((s64)cubic * quadratic) >> 12) / 2);
    float cubicSqF;
    float cubicFourthF;
    s64 cubicFourth;
    s64 depConstant;
    s64 quadraticTerm;
    fx32 resolventRoots[3];
    u8 i;

    /* Ferrari: depress, then solve the resolvent cubic */
    cubicSqF = (s64)cubicSq / 4096.0f;
    cubicFourthF = cubicSqF * cubicSqF;
    cubicFourth = (s64)(cubicFourthF > 0 ? 4096.0f * cubicFourthF + 0.5f : 4096.0f * cubicFourthF - 0.5f);
    quadraticTerm = (((s64)cubicSq * quadratic) >> 12) / 16;
    depConstant = constant + (quadraticTerm + cubicFourth * -3 / 256 - (((s64)cubic * (s32)(u32)linear) >> 12) / 4);
    func_0204c200(-depQuadratic / 2, -depConstant,
                  (((depConstant * depQuadratic) >> 12) * 4 - ((depLinear * depLinear) >> 12)) / 8, resolventRoots);
    if (resolventRoots[0] == 0x7fffffff) {
        for (i = 0; i < 12; i++)
            roots[i] = 0x7fffffff;
        return;
    }
    for (i = 0; i < 3; i++) {
        u8 base = i * 4;
        fx32 slope;
        fx32 offset;
        fx32 sum;
        if (resolventRoots[i] != 0x7fffffff) {
            sum = resolventRoots[i] * 2 - depQuadratic;
            if (sum > -0x80) {
                if (sum < 0)
                    sum = 0;
                slope = FX_Sqrt_01ff9cfc(sum);
                offset = FX_Sqrt_01ff9cfc((fx32)((((s64)resolventRoots[i] * resolventRoots[i]) >> 12) - depConstant));
                if (depLinear >= 0) {
                    SolveMonicQuadratic_0204c17c(slope, resolventRoots[i] - offset, &roots[base], &roots[base + 1]);
                    SolveMonicQuadratic_0204c17c(-slope, offset + resolventRoots[i], &roots[base + 2], &roots[base + 3]);
                } else {
                    SolveMonicQuadratic_0204c17c(slope, offset + resolventRoots[i], &roots[base], &roots[base + 1]);
                    SolveMonicQuadratic_0204c17c(-slope, resolventRoots[i] - offset, &roots[base + 2], &roots[base + 3]);
                }
            } else {
                roots[base + 3] = 0x7fffffff;
                roots[base + 2] = 0x7fffffff;
                roots[base + 1] = 0x7fffffff;
                roots[base] = 0x7fffffff;
            }
        } else {
            roots[base + 3] = 0x7fffffff;
            roots[base + 2] = 0x7fffffff;
            roots[base + 1] = 0x7fffffff;
            roots[base] = 0x7fffffff;
        }
    }
    for (i = 0; i < 12; i++) {
        if (roots[i] != 0x7fffffff)
            roots[i] -= cubic / 4;
    }
}
