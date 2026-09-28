void *G2_GetBG0ScrPtr_02006de0(void) {
    int scrBase = (*(volatile unsigned short *)0x04000008 & 0x1f00) >> 8;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x38000000) >> 27;
    return (void *)(0x06000000 + (dispBase << 16) + (scrBase << 11));
}
