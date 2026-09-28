void *G2S_GetBG0CharPtr_020070ac(void) {
    int slot = (*(volatile unsigned short *)0x04001008 & 0x3c) >> 2;
    return (void *)(0x06200000 + (slot << 14));
}
