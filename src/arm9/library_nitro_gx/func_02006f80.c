void *G2_GetBG3ScrPtr_02006f80(void) {
    int mode = *(volatile unsigned *)0x04000000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400000e;
    unsigned base = ((*(volatile unsigned *)0x04000000 & 0x38000000) >> 27) << 16;
    unsigned slot = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0:
    case 1:
    case 2:
        return (void *)(0x06000000 + base + (slot << 11));
    case 3:
    case 4:
    case 5:
        if ((cnt & 0x80) != 0) {
            return (void *)(0x06000000 + (slot << 14));
        }
        return (void *)(0x06000000 + base + (slot << 11));
    case 6:
        return 0;
    default:
        return 0;
    }
}
