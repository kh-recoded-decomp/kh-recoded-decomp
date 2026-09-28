unsigned FX_GetSqrtResult_01ff9db8(void) {
    while (*(volatile unsigned short *)0x040002b0 & 0x8000) {
    }
    return (*(volatile unsigned *)0x040002b4 + 0x200) >> 10;
}
