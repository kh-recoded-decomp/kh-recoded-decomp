void *G2_GetBG0CharPtr_02007078(void) {
    int slot = (*(volatile unsigned short *)0x04000008 & 0x3c) >> 2;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
    return (void *)(0x06000000 + (dispBase << 16) + (slot << 14));
}
