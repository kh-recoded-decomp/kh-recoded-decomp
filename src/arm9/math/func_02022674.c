extern void func_02021b08(int *out, int a, int b);
extern int func_02021a04(int *ptr, int addend);

int func_02022674(int *numerator, int denominator, int *accumulator, int unused)
{
    int out[2];
    func_02021b08(out, *numerator, denominator);
    *numerator = out[1];
    return func_02021a04(accumulator, out[0]);
}
