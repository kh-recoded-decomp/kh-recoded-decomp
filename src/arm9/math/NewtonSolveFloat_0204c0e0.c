#include "nitro/types.h"

typedef float (*NewtonFunc)(float x, float target, float arg);
typedef float (*NewtonDeriv)(float x, float target);

extern double Fabs_02022ac4(double x);
extern float DoubleToFloat_02023538(double x);

float NewtonSolveFloat_0204c0e0(float x, float target, float arg, NewtonFunc func, NewtonDeriv deriv, float epsilon)
{
    u16 iter;
    float next;

    for (iter = 0; iter < 1000; iter++) {
        next = x - func(x, arg, target) / deriv(x, target);
        if (DoubleToFloat_02023538(Fabs_02022ac4(next - x)) < epsilon) {
            return next;
        }
        x = next;
    }
    return next;
}
