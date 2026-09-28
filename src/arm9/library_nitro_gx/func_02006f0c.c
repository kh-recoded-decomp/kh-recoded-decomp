void *G2S_GetBG2ScrPtr_02006f0c(void) {
    int mode = *(volatile unsigned *)0x04001000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400100c;
    unsigned slot = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return (void *)(0x06200000 + (slot << 11));
    case 5:
        if ((cnt & 0x80) != 0) {
            slot <<= 14;
        } else {
            slot <<= 11;
        }
        return (void *)(0x06200000 + slot);
    case 6:
        return 0;
    default:
        return 0;
    }
}
