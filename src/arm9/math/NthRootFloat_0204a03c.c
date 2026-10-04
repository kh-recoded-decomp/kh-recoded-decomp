#include "nitro/types.h"

extern double Fabs_02022ac4(double x);
extern float func_02023538(double value);
extern void PowThenAddFloat_02049e30();
extern void PowDerivativeTimesN_02049e6c();
extern float func_0204c0e0(float guess, int n, float value, void (*func)(), void (*deriv)(), float tolerance);

float NthRootFloat_0204a03c(float value, int n)
{
    float magnitude;
    float guess;

    if (0.0f == value) {
        return 0.0f;
    }
    magnitude = func_02023538(Fabs_02022ac4(value));
    if (magnitude < 1e-6f) {
        guess = 5000.0f * value;
    } else if (magnitude < 1e-4f) {
        guess = 300.0f * value;
    } else if (magnitude < 0.01f) {
        guess = 20.0f * value;
    } else if (magnitude < 1.0f) {
        guess = 2.0f * value;
    } else if (magnitude < 10.0f) {
        guess = 0.5f * value;
    } else if (magnitude < 1000.0f) {
        guess = 0.01f * value;
    } else {
        guess = 1e-4f * value;
    }
    return func_0204c0e0(guess, n, value, PowThenAddFloat_02049e30, PowDerivativeTimesN_02049e6c, 1.0f / 256.0f);
}
