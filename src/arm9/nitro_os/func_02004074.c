int OS_GetTickLo(void) {
    return *(volatile unsigned short *)0x04000100;
}
