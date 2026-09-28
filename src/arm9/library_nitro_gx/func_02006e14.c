void *G2S_GetBG0ScrPtr_02006e14(void) {
    int slot = (*(volatile unsigned short *)0x04001008 & 0x1f00) >> 8;
    return (void *)(0x06200000 + (slot << 11));
}
