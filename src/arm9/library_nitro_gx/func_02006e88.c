void *G2_GetBG2ScrPtr_02006e88(void) {
    int mode = *(volatile unsigned *)0x04000000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400000c;
    unsigned base = ((*(volatile unsigned *)0x04000000 & 0x38000000) >> 27) << 16;
    unsigned slot = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return (void *)(0x06000000 + base + (slot << 11));
    case 5:
        if ((cnt & 0x80) != 0) {
            return (void *)(0x06000000 + (slot << 14));
        }
        return (void *)(0x06000000 + base + (slot << 11));
    case 6:
        return (void *)0x06000000;
    default:
        return 0;
    }
}
