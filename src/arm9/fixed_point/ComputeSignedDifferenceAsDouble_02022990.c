extern double func_0202363c(int value);
extern double func_02022e20(double a, double b);

double ComputeSignedDifferenceAsDouble_02022990(int a, int b)
{
    if (a >= b) {
        return func_0202363c(a - b);
    }
    return func_02022e20(0.0, func_0202363c(b - a));
}
