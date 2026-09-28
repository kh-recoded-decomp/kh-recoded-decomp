void FX_InvAsync_01ff9d88(int x) {
    volatile unsigned *div = (volatile unsigned *)0x04000280;
    *(volatile unsigned short *)div = 1;
    *(volatile long long *)(div + 4) = (long long)0x1000 << 32;
    *(volatile long long *)(div + 6) = (long long)(unsigned)x;
}
