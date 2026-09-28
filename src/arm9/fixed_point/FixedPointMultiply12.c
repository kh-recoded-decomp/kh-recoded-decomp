/* Based on src/auto/func_02005418.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
int FixedPointMultiply12(int left, int right)
{
    return ((long long)left * right + 0x800) >> 12;
}
