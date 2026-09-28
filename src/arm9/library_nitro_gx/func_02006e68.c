void *G2S_GetBG1ScrPtr_02006e68(void) {
    int slot = (*(volatile unsigned short *)0x0400100a & 0x1f00) >> 8;
    return (void *)(0x06200000 + (slot << 11));
}
