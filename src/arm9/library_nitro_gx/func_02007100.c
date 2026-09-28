void *G2S_GetBG1CharPtr_02007100(void) {
    int slot = (*(volatile unsigned short *)0x0400100a & 0x3c) >> 2;
    return (void *)(0x06200000 + (slot << 14));
}
