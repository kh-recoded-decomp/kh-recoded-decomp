void *G2_GetBG1CharPtr_020070cc(void) {
    int slot = (*(volatile unsigned short *)0x0400000a & 0x3c) >> 2;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
    return (void *)(0x06000000 + (dispBase << 16) + (slot << 14));
}
