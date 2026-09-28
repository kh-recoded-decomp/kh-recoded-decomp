long long func_01ff9d30(void) {
    volatile unsigned short *reg_divcnt = (volatile unsigned short *)0x04000280;
    while (*reg_divcnt & 0x8000)
        ;
    return *(long long *)0x040002a0;
}
