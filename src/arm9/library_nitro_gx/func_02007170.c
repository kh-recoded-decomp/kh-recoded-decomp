void *G2S_GetBG2CharPtr_02007170(void) {
    int mode = *(volatile unsigned *)0x04001000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400100c;
    if (mode < 5 || (cnt & 0x80) == 0) {
        return (void *)(0x06200000 + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}
