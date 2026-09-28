int FixedPointMultiply12(int left, int right)
{
    return ((long long)left * right + 0x800) >> 12;
}
