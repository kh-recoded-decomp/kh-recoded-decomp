extern int func_02021b80(int a, int b);

int func_02022570(int value)
{
    if (func_02021b80(value, 4) == 0) {
        if (func_02021b80(value, 100) != 0 || func_02021b80(value, 400) == 100) {
            return 1;
        }
    }
    return 0;
}
