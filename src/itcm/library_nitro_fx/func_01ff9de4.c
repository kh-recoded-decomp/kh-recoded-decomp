void FX_DivAsync_01ff9de4(int numer, int denom) {
    volatile unsigned *div = (volatile unsigned *)0x04000280;
    *(volatile unsigned short *)div = 1;
    div[4] = 0;
    div[5] = (unsigned)numer;
    div[6] = (unsigned)denom;
    div[7] = 0;
}
