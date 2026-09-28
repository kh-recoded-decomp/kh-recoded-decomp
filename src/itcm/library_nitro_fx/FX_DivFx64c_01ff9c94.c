extern void FX_DivAsync(int num, int denom);

long long FX_DivFx64c_01ff9c94(int num, int denom)
{
    volatile unsigned short *reg_divcnt = (volatile unsigned short *)0x04000280;
    FX_DivAsync(num, denom);
    while (*reg_divcnt & 0x8000) {
    }
    return *(long long *)0x040002a0;
}
